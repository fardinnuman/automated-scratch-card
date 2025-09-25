<div align="center">

# <a href="https://archiveprogram.github.com/"><img src="https://raw.githubusercontent.com/acervenky/animated-github-badges/master/assets/acbadge.gif" width="26" height="26"></a> Automated Scratch Card <a href="https://archiveprogram.github.com/"><img src="https://raw.githubusercontent.com/acervenky/animated-github-badges/master/assets/acbadge.gif" width="26" height="26"></a>

![C](https://img.shields.io/badge/Programming-blue?style=for-the-badge&logo=c&logoColor=white)
	![Course](https://img.shields.io/badge/CSE%201101-Structured%20Programming-blue?style=for-the-badge&logo=read-the-docs&logoColor=white)

This **C program** was developed as a part of my **CSE 1101 (Structured Programming)** course. It demonstrates fundamental concepts of the C language, including **variables, loops, functions, arrays, strings, basic input/output and file handling**, simulating an automated scratch card system for prepaid mobile recharges with **admin/user** management

</div>

---
<div align="center">

## 📂 FEATURES

</div>

### **I. Login System**
- Admin: `admin` / `admin123`  
- User: `user` / `mobile number`  
   
### **II. User Features**
- 📞 **Login via Mobile Number**: Secure user authentication  
- ⚡ **Recharge with Card**: Apply valid recharge cards to add account minutes  
- 🔒 **Autolock**: Account locks automatically after 3 invalid attempts

> Transaction history is saved automatically   

### **III. Admin Features**
- 🎨 **Create New Cards**: Generate multiple recharge cards with specific minutes and prices with unique 20-digit numbers  
- ❌ **Delete Cards**: Remove invalid or unwanted cards 
- 🔓 **Unlock User Accounts**: Reset locked user accounts  
- 📝 **History Logs**: View all recharge activities  
- 📊 **Statistics**: Track total cards sold, remaining cards and revenue by card type  
- 🔎 **Search Transactions**: Look up all past transactions for a specific mobile number  

---

<div align="center">

## ⚙️ TECHNOLOGIES USED 

| Category | Technology | Purpose |
| --- | --- | --- |
| **💻 Core Language** | **C Programming** | Implements program logic, menus, user/admin workflows and card operations |
| **🗂 Data Structures** | **Structs (`struct`)** | Represent users (`User_179`) and cards (`Card_179`) with multiple attributes |
|  | **Arrays** | Store multiple users/cards and enable iteration/search |
| **📁 File Operations** | **File I/O (`fopen`, `fclose`, `fprintf`, `fscanf`)** | Persist users, cards and transaction history (`users.txt`, `cards.txt`, `history.txt`) |
| **🎲 Randomization** | **`rand()`** | Generate unique 20-digit scratch card numbers |
| **⏱ Time Handling** | **`time.h`, `localtime()`** | Timestamp transactions automatically (date & time) |
| **🔤 String Operations** | **`strcmp`, `strcpy`** | Compare and copy strings for login, validation and data storage |
| **🔀 Control Flow** | **Loops (`for`, `while`)** | Iterate over users/cards and navigate menus |
|  | **Conditionals (`if`, `else`)** | Handle login, card validation, account lock/unlock and admin/user workflows |
| **📦 Modular Programming** | **Functions** | Modularize code: `login()`, `userMenu_179()`, `adminMenu_179()`, `generateCardNumber_179()`, `addHistory_179()`, save/load functions |
| **🖥 User Interaction** | **`scanf`, `printf`** | Interactive console input/output for users/admins |
| **🔒 Security & Validation** | Account Locking | Lock accounts after 3 invalid attempts; admin can unlock |
|  | Card Validation | Prevent duplicate card usage; ensure only valid cards are applied |
| **⚡ Automation Features** | Auto-Card Generation | Generate a new card automatically after each successful recharge |
| **📊 Reporting & Analytics** | Statistics | Calculate total cards sold, remaining cards, revenue per card type |
|  | Transaction History | Search logs by mobile number with card number, minutes, date and time |
| **⚠️ Error Handling & Feedback** | Input Validation | Handles invalid logins, wrong passwords, non-existing cards and empty history gracefully |
| **💰 Randomized Pricing** | Price Assignment | Assign card prices based on minutes (40, 60, 100) and update statistics automatically |

---

## 🧩 USER INTERFACE | HOW IT WORKS?

</div>

### 0. **Program Startup**

When you run it, the first output will be:

```c
Submitted by:
Fardin Bin Aslam Numan
Roll: 2403179
Section: C

• To log in as admin, enter 'admin' and 'admin123' as the credentials
• To log in as user, enter 'user' and then mobile number
```

---

### 1. **Login Panel**

Next, it will ask:

```c
~~~~~ Login Panel ~~~~~
Enter Login(admin/user):
```

### 1.1. **`User` Login Panel**


- If you type `user`, it asks: 

```c
Enter Mobile Number:
```

* After entering `mobile number` it will enter **User Menu**

### 1.2. **`Admin` Login Panel**

- If you type `admin`, it asks:

```c
Enter Password:
```

- If you type `admin123`, it will enter **Admin Menu**

- If wrong password, it prints:

```c
Invalid login. Try again
```


---

### 2. **User Menu**

After entering mobile number:

- If your account is locked:

```c
Enter Mobile Number: 01406369675
Your account is locked. Contact admin
```

- If account is not locked, it asks for a card number:

```c
Enter Mobile Number: 01406369675
Enter Card Number:
```

- If card is invalid or already used:

```c
Enter Mobile Number: 01406369675
Enter Card Number: 97476960605088712993 // invalid card number
Invalid or already used card!
```

- After 3 invalid attempts:

```c
Account locked after 3 invalid attempts
```

- If the card is valid:

```c
Enter Mobile Number: 01406369675
Enter Card Number: 36359857960193707092 // valid card number
Reload Successful
```

>Then it saves the transaction in `history.txt` and generates a new card automatically

---

### 3. **Admin Menu**

After successful admin login:

```c
--- Admin Menu ---
1. New Card
2. Delete Card
3. Unlock Card
4. History
5. Statistics
6. Search
7. Exit
Enter your option:
```

#### 3.1. New Card

```c
Enter your option: 1
How many cards and minute: 100 40 // 100 cards 40 minutes
100 Cards Creation Successful
```

> This generates 100 cards of 40 minutes in `card.txt` 

#### 3.2. Delete Card

```c
Enter your option: 2
Enter Card Number:
```
- If right card number is given:
```c
Enter Card Number: 68622217439292148645 // right card number
Card Deletion Successful
```
- If wrong card number is given:
```c
Enter Card Number: 2443279472749 // wrong card number
Card not found
```

#### 3.3. Unlock Card

- After a card got locked because of 3 wrong attempts by the user, admin can unlock the card using this option:

```c
Enter your option: 3
Enter Mobile Number: 01406369675
Card Unlock Successful
```

#### 3.4. History
    
- Prints all entries in `history.txt`:

```c
Enter your option: 4

Card No              Date       Time  Minute Mobile No
12345678901234567890 25/09/2025 20:30 40     01406369675
```

#### 3.5. Statistics

- Prints information of total cards sold, remaining cards and revenue from `user.txt`:

```c
Enter your option: 5

Total Cards Sold:  40 min:5  60 min:3  100 min:2
Total Cards Remains:  40 min:995  60 min:997  100 min:998
Total Amounts Sold in Tk.:  40 min:250  60 min:210  100 min:240

```

#### 3.6. Search

- Prints transaction history of mobile number:

```c
Enter your option: 6
Enter Mobile Number: 01406369675

Card No              Date       Time  Minute
72274075476924695937 25/09/2025 21:11 40    
Total Transactions: 1
```
- If a user reloaded 40 minutes twice:

```c
Enter your option: 6
Enter Mobile Number: 01406369675

Card No              Date       Time  Minute
72274075476924695937 25/09/2025 21:11 40 
09876543210987654321 25/09/2025 20:32 40
Total Transactions: 2
```

#### 3.7. Exit

- This will take back to the login menu:

```c
Enter your option: 7
~~~~~ Login Panel ~~~~~
Enter Login(admin/user): 
```





