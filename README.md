
#  Library Management System in C


## what iss itt ?

- **Search & Sort**: search for books by title, author, or year, and sort results by title or year. - i used bubble sort
- **Librarian Actions**: Librarians can add and delete books, with 'maybe' plans for modifying book records.
- **Retro ui**: I like the retro look a lot so why not?

---

## Tech Stack

### Backend:
- **C**: Core logic for searching, sorting, and managing books.
- **Node.js**: talks with ui and the C file.
- **Express.js**: RESTful routes.
  
### Frontend:
- **HTML/CSS**
- **NES.css**
- **JavaScript**

### Database (Future Plan):
- **CSV (Current)**: Csv for now haha
- **SQL (Future)**: probably **SQLite** or **MySQL** 

---

## you can try it !

1. Clone the repository:
   ```bash
   git clone https://github.com/INAHIDC/DR.BOOKMAN.git
   cd Book Keeper
   ```

2. Compile the **C files**
  

3. Run the librarian program

4. Set up the front-end server (You need to have Node.js)
   ```bash
   node server.js
   ```

### Members:
-  `/member` lets you search and sort books.
- type a title, author, or year, and click "Search." and then sort results by title or year after searching.

### Librarians:
-  `/librarian`, log in with the password `knowledge`, and manage the library.

## Files Treeee

```
/dr-bookman
    ├── book_manager.c        # main logic
    ├── librarian.c           # Librarian functions
    ├── books.csv             # Book storage
    ├── server.js             # Node.js  for front end
    ├── public
    │   ├── index.html        # Ni stands for Intuitive Introverts (a carl yungs theory)
    │   ├── member.html       # search page
    │   ├── librarian.html    # Librarian page
    └── README.md             
```

## Maybe Plans (maybe ill maybe not)

1. **Move to SQL**: maybe move from the CSV file to a relational db like **SQL**
2. **More Librarian Functions**:  features like modifying book details, borrowing/returning functionality
3. **Gamification**: because im a gamer i think will add grammar challenges or quizzes, turning it into a small game with points and leaderboards? 

---

