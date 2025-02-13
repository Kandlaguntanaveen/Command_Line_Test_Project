# Command-Line_Test (C Programming)

hi bro

This project is a Command-Line Interface (CLI) application developed in C that allows users to register, sign in, take a quiz, and view the results. The system validates the input files, handles user sign-up and sign-in, and provides a quiz interface.

## Features

- **File Validation:** Ensures the correct files (user data, passwords, questions, and answers) are provided and accessible.
- **User Sign-Up:** Allows users to register with a unique username and password.
- **Password Visibility Option:** Provides an option to show or hide the password during entry.
- **Password Validation:** Enforces password strength criteria (at least 8 characters, one uppercase letter, one lowercase letter, one digit, one special character, and no spaces).
- **User Sign-In:** Enables users to sign in with their registered username and password.
- **Quiz:** Users can take a quiz after signing in by answering questions one by one.
- **Answer Validation:** Users must input valid options for each question, with the option to retry on invalid input.
- **Result Summary:** After completing the quiz, users see a summary of their results, showing correct and incorrect answers.

## Project Setup

### Prerequisites

- C Compiler (GCC Ubuntu 13.3.0-6ubuntu2~24.04)
- Command-line interface (CLI)

### File Structure

Ensure the following text files are provided and formatted correctly:

1. `userdata.csv` – Contains the user data (should start with the word "Userdata").
2. `password.csv` – Contains the user passwords (should start with the word "Password").
3. `questions.txt` – Contains the quiz questions (should start with the word "Questions").
4. `answers.txt` – Contains corresponding answers for the quiz questions (should start with the word "Answers").

# Running the Program
To run the program, use the following command in the terminal with the required 4 arguments (the file paths for userdata, password, questions, and answers):
```bash
./a.out user_info.csv Passwords.csv Questions.txt Answers.txt
```

# Usage
### 1. File Validation
- The program expects exactly 4 arguments (userdata, password, questions, and answers).
- If the file paths are incorrect or files are missing, the program will print an error message and terminate, asking you to provide the correct files.
### 2. User Sign-Up
- When prompted for a username, the system will check if it already exists in the userdata.txt file.
- If the username is already taken, the user will be prompted to choose another one.
- After entering a valid username, the user will be asked to create a password.
- The password must meet the following requirements:
   - Minimum length of 8 characters.
   - At least one uppercase letter.
   - At least one lowercase letter. 
   - At least one digit.
   - At least one special character. 
   - No spaces.
- If the password meets all criteria, it is saved in the password.txt file, and the sign-up process is completed.
- If the password is invalid, the program will exit and prompt an error message.
### 3. User Sign-In
- After signing up, the user can sign in by entering their username and password.
- If the username exists, the system will prompt the user to enter the password.
- If the entered password matches the stored password, the user will gain access to the quiz.
- If the password does not match, the program will allow the user to retry up to a set number of attempts.
### 4. Taking the Quiz
- After signing in successfully, the program will display each question from the questions.txt file one by one.
- The user must choose an option by entering a valid number (e.g., 1, 2, 3, etc.).
- If the user enters an invalid option, the program will prompt them to choose again.
### 5. Result Summary
- After the last question, the program will display a completion message with the number of correct and incorrect answers.
- The results summary will indicate how well the user performed in the quiz.

## Error Handling

### 1. Invalid Command-Line Arguments

- The program expects **exactly 4 arguments**:
  1. `userdata.csv` – Contains user data (should start with the word **"Userdata"**).
  2. `password.csv` – Contains passwords (should start with the word **"Password"**).
  3. `questions.txt` – Contains quiz questions (should start with the word **"Questions"**).
  4. `answers.txt` – Contains the corresponding answers (should start with the word **"Answers"**).

- If the **files are missing** or the **number of arguments is incorrect**, the program will display an error message and prompt the user to provide the correct file paths.
- The program **will not proceed** until valid files are supplied.

---

### 2. Password Criteria Failure

When the user creates a password, it must meet the following criteria:
- At least **8 characters** long.
- Contains at least:
  - One **uppercase letter**.
  - One **lowercase letter**.
  - One **digit**.
  - One **special character**.
- **Does not contain spaces**.
- If the password does **not** meet these requirements, the system will display the following error message and prompts the user to re-enter upto some attempts:
  - **Password does not meet the required criteria. Try Again.**
- After the maximum number of attempts is reached, the system will terminate the sign-up process for that user.
- The user **will not be able to proceed** further until a valid password is entered.

---

### 3. Incorrect Password or Username

During the **sign-in process**, the program will check if the entered username exists:
- If the **username does not exist**, the system will display the following error message:
  - **User does not exists. SignUp First then SignIn! Sign in failed**
- If the **username exists** but the **password is incorrect**, the user will be allowed to re-enter the password, up to a set number of retries.
- The user will have a **set number of attempts** (e.g., **3 attempts**) to enter the correct password.
- If the password is still incorrect after the maximum number of attempts, then system will display the following message:
  - **Too Many Failed Attempts, Exiting the process.** 
- Once the **maximum number of attempts** is reached, the system will **Terminate** the sign-in process for that user.

## Notes
- The program reads and writes to the text files (userdata.csv, password.csv, questions.txt, answers.txt), so ensure that these files are formatted correctly and located in the same directory as the program or provide the correct file paths.
- Make sure that the files follow the format expected (e.g., "Userdata", "Password", "Questions", "Answers" at the beginning of each file).

## Contributing
- Fork the repository.
- Create a new branch for your feature or bugfix.
- Make your changes and commit them.
- Push to your fork and create a pull request.






