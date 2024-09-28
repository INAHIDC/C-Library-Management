const express = require('express');
const bodyParser = require('body-parser');
const { spawn } = require('child_process');
const app = express();
app.use(bodyParser.json());
app.use(express.static('public')); 


app.get('/member', (req, res) => {
    res.sendFile(__dirname + '/public/member.html');
});

app.get('/member/search', (req, res) => {
    const query = req.query.q;

    const searchBooks = spawn('./librarian', ['search', query]);

    searchBooks.stdout.on('data', (data) => {
        res.send(data.toString());
    });

    searchBooks.stderr.on('data', (data) => {
        res.status(500).send(`Error: ${data.toString()}`);
    });
});

app.get('/member/sort', (req, res) => {
    const sortBy = req.query.sortBy;

    const sortBooks = spawn('./librarian', ['sort', sortBy]);

    sortBooks.stdout.on('data', (data) => {
        res.send(data.toString());
    });

    sortBooks.stderr.on('data', (data) => {
        res.status(500).send(`Error: ${data.toString()}`);
    });
});


app.get('/member/list', (req, res) => {
    const listBooks = spawn('./book_manager', ['list']); 

    listBooks.stdout.on('data', (data) => {
        res.send(data.toString());
    });

    listBooks.stderr.on('data', (data) => {
        res.status(500).send(`Error: ${data.toString()}`);
    });
});

// librarian
app.get('/librarian', (req, res) => {
    res.sendFile(__dirname + '/public/librarian.html');
});

app.post('/librarian/add', (req, res) => {
    const { title, author, year } = req.body;

    const addBook = spawn('./book_manager', ['add', title, author, year]);

    addBook.stdout.on('data', (data) => {
        res.send(data.toString());
    });

    addBook.stderr.on('data', (data) => {
        res.status(500).send(`Error: ${data.toString()}`);
    });
});

app.post('/librarian/delete', (req, res) => {
    const { title } = req.body;

    const deleteBook = spawn('./book_manager', ['delete', title]);

    deleteBook.stdout.on('data', (data) => {
        res.send(data.toString());
    });

    deleteBook.stderr.on('data', (data) => {
        res.status(500).send(`Error: ${data.toString()}`);
    });
});

// Start
app.listen(3000, () => {
    console.log('Server running on http://localhost:3000');
});
