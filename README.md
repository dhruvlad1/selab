# Student Internship Portal

**A Software Engineering Project Demonstrating Automated Internship Recruitment & Structural Testing**

![Status](https://img.shields.io/badge/Status-Complete-brightgreen) ![Language](https://img.shields.io/badge/Language-C%2B%2B11-blue) ![Testing](https://img.shields.io/badge/Tests-30%2F30%20Passed-success)

---

## Project Identity

**Institution:** Veermata Jijabai Technological Institute (VJTI), Mumbai  
**Course:** Computer Engineering (2nd Year, B.Tech)  
**Academic Context:** Software Engineering Principles - Structural Testing & Software Architecture  
**Project Type:** Command-Line Interface (CLI) Application

### Purpose

A demonstration of professional software engineering practices through a **Student Internship Portal** that automates internship recruitment workflows with comprehensive eligibility validation and quality assurance via structural testing.

---

## Overview

The Student Internship Portal is a CLI-based system that streamlines the internship recruitment process across four primary stakeholders:

- **Student** - Search, apply for internships with automatic eligibility validation
- **Company HR** - Post internship listings, review and shortlist applications, conduct interviews
- **Faculty Mentor** - Monitor student progress, verify internship completion, approve NOC
- **Placement Officer** - Track placement analytics, oversee placement activities

### Key Features

[OK] Automated CGPA eligibility verification
[OK] Application limit enforcement (max 5 per student)
[OK] Internship status management (open/closed)
[OK] Resume validation
[OK] Faculty verification workflow
[OK] Real-time application tracking
[OK] In-memory data persistence using STL containers

---

## Architecture: Entity-Boundary-Control (EBC) Pattern

The system strictly follows the **Entity-Boundary-Control architectural pattern**, a software engineering best practice that separates concerns into three layers:

### Pattern Breakdown

| Component          | Role                         | Objects                               | Responsibility                                               |
| ------------------ | ---------------------------- | ------------------------------------- | ------------------------------------------------------------ |
| **Entity Layer**   | Core business objects        | Student, Internship, Application      | Persistent data and core state of the system                 |
| **Boundary Layer** | User interaction interface   | ApplicationForm, NotificationToast    | Interfaces through which users interact with the system      |
| **Control Layer**  | Business logic orchestration | ApplicationManager, ValidationService | Flow coordination, eligibility checks, application lifecycle |

### Canonical EBC Objects

The system uses exactly seven canonical objects in the Entity-Boundary-Control pattern:

**Entities (Data & State):**

- `Student` - Represents a student with ID, CGPA, application count, and skills
- `Internship` - Represents an internship position with domain, status, and eligibility criteria
- `Application` - Represents a student's application with status, resume, and verification state

**Boundary Objects (User Interface):**

- `ApplicationForm` - Interface for students to submit internship applications
- `NotificationToast` - Interface for system notifications and feedback to users

**Control Objects (Business Logic):**

- `ApplicationManager` - Orchestrates application workflow and lifecycle management
- `ValidationService` - Enforces business rules and eligibility validation

### Architecture Diagram

```
+-----------BOUNDARY LAYER-------------------+
|  - ApplicationForm                         |
|  - NotificationToast                       |
+----+-------+-------+-----+----+-------+---+
      |
      | User Actions
      v
+-----------CONTROL LAYER-------------------+
|  - ApplicationManager                      |
|  - ValidationService                       |
+----+-------+-------+-----+----+-------+---+
      |
      | Data Operations
      v
+-----------ENTITY LAYER--------------------+
|  - Student                                 |
|  - Internship                              |
|  - Application                             |
+-----+-----+-----+-----+-----+-----+-----+--+
```

### Core Entities

#### 1. **Student Entity**

```cpp
struct Student {
    int studentID;                    // Unique identifier
    float cgpa;                       // Cumulative GPA (0-10 scale)
    int currentApplicationCount;      // Active applications (0-5)
    std::vector<std::string> skills;  // Skill tags
};
```

#### 2. **Internship Entity**

```cpp
struct Internship {
    int internshipID;           // Unique identifier
    std::string domain;         // Field (Web Dev, FinTech, etc.)
    bool isOpened;              // Recruitment status
    float minCgpa;              // Minimum eligibility threshold
};
```

#### 3. **Application Entity**

```cpp
struct Application {
    int studentID;              // Foreign key to Student
    int internshipID;           // Foreign key to Internship
    std::string resume;         // Resume file reference
    std::string status;         // Pending, Shortlisted, Selected
    bool facultyVerified;       // Completion verification flag
};
```

---

## Business Rules & Constraints

The system enforces five critical business rules to ensure data integrity:

### Rule 1: CGPA Eligibility Threshold

[OK] REQUIREMENT: Student CGPA >= Internship Minimum CGPA
[NO] REJECTION: Student CGPA < Internship Minimum CGPA (typically 6.0)

**Impact:** Ensures only qualified candidates advance to HR review.

### Rule 2: Application Count Limit

[OK] ALLOWED: Student current applications < 5
[NO] REJECTED: Student has already submitted 5 applications

**Impact:** Prevents application spam and ensures quality over quantity.

### Rule 3: Internship Status Verification

[OK] ALLOWED: Internship.isOpened == true
[NO] REJECTED: Internship.isOpened == false

**Impact:** Ensures no applications are accepted for closed positions.

### Rule 4: Resume Validation

[OK] ALLOWED: Resume filename is non-empty string
[NO] REJECTED: Resume filename is empty or null

**Impact:** Guarantees applicants provide documentation.

### Rule 5: Student & Internship ID Validation

[OK] ALLOWED: Valid IDs (> 0)
[NO] REJECTED: Invalid IDs (<= 0)

**Impact:** Prevents data corruption from malformed IDs.

---

## Testing Strategy: Structural Testing Approach

This project demonstrates professional **structural testing** through 30 comprehensive test cases organized in two complementary methodologies.

### Test Coverage Philosophy

The testing strategy achieves **three levels of code coverage**:

1. **Statement Coverage** - Every line of code executed
2. **Branch Coverage** - Every conditional path tested
3. **Path Coverage** - Complex combinations verified

---

### Section A: White Box Testing (15 Test Cases)

**Definition:** Testing internal logic with knowledge of source code structure.

**Coverage Path Map (applyForInternship function):**

| Path | Condition             | Test Case                  |
| ---- | --------------------- | -------------------------- |
| P1   | Invalid Student ID    | Check if studentID <= 0    |
| P2   | Invalid Internship ID | Check if internshipID <= 0 |
| P3   | CGPA Eligibility      | Verify CGPA >= minCgpa     |
| P4   | Application Limit     | Verify count < 5           |
| P5   | Internship Status     | Verify isOpened == true    |
| P6   | Resume Validation     | Verify resume non-empty    |

#### Test Case Summary

| ID   | Coverage Target        | Scenario                            | Expected                | Actual                  | Status |
| ---- | ---------------------- | ----------------------------------- | ----------------------- | ----------------------- | ------ |
| 1    | Path 1 + Statement     | Valid path with all criteria met    | Pass: Success           | Pass: Success           | [OK]   |
| 2    | Path 2 + Student ID    | Invalid Student ID (0)              | Fail: Invalid ID        | Fail: Invalid ID        | [OK]   |
| 3    | Path 3 + Internship ID | Invalid Internship ID (-1)          | Fail: Invalid ID        | Fail: Invalid ID        | [OK]   |
| 4    | Path 4 + CGPA Branch   | CGPA 5.5 < Min 6.0                  | Fail: Low CGPA          | Fail: Low CGPA          | [OK]   |
| 5    | Path 5 + Limit Branch  | App Count = 5 (at limit)            | Fail: Limit Reached     | Fail: Limit Reached     | [OK]   |
| 6    | Path 6 + Open Branch   | Internship closed (isOpened=false)  | Fail: Internship Closed | Fail: Internship Closed | [OK]   |
| 7    | Path 7 + Resume Branch | Empty resume string                 | Fail: Missing Resume    | Fail: Missing Resume    | [OK]   |
| 8-15 | Path Combinations      | Various edge cases and combinations | All Pass                | All Pass                | [OK]   |

**Coverage Achievement:**

- ✓ 100% Statement Coverage
- ✓ 100% Branch Coverage
- ✓ Path Coverage for critical logic flows

---

### Section B: Black Box Testing (15 Test Cases)

**Definition:** Testing functionality without knowledge of internal implementation, focusing on input/output behavior.

#### Testing Technique 1: Boundary Value Analysis (BVA)

Tests the **boundaries** where behavior changes occur.

| Test ID | Parameter  | Boundary Test    | Input | Expected            | Rationale                 |
| ------- | ---------- | ---------------- | ----- | ------------------- | ------------------------- |
| 16      | CGPA       | Just Below Limit | 5.99  | Fail: Low CGPA      | Boundary case             |
| 17      | CGPA       | Exact Boundary   | 6.00  | Pass: Success       | Critical transition point |
| 18      | CGPA       | Just Above Limit | 6.01  | Pass: Success       | Boundary case             |
| 19      | App Count  | Below Limit      | 4     | Pass: Success       | Within range              |
| 20      | App Count  | At Limit         | 5     | Fail: Limit Reached | Critical threshold        |
| 21      | App Count  | Over Limit       | 6     | Fail: Limit Reached | Out of range              |
| 29      | Student ID | Minimum Valid    | 1     | Pass: Success       | Valid lower bound         |
| 30      | Student ID | Minimum Invalid  | 0     | Fail: Invalid ID    | Invalid lower bound       |

**BVA Principle:** "Bugs tend to hide at boundaries" - By testing exact boundaries (6.0, 5, etc.) and off-by-one values (5.99, 6.01), we catch rounding errors and boundary condition bugs.

#### Testing Technique 2: Equivalence Class Partitioning (ECP)

Groups inputs into **equivalence classes** where all values behave identically.

| Test ID | Input Class       | Representative | Expected | Justification                        |
| ------- | ----------------- | -------------- | -------- | ------------------------------------ |
| 22      | Valid CGPA        | 8.5            | Pass     | All values >= 6.0 behave identically |
| 23      | Invalid CGPA      | 2.0            | Fail     | All values < 6.0 behave identically  |
| 24      | Out-of-Range CGPA | -1.0           | Fail     | Negative values handled as invalid   |
| 25      | Valid Resume      | "my_cv.pdf"    | Pass     | Non-empty strings are valid          |
| 26      | Invalid Resume    | ""             | Fail     | Empty string is invalid              |
| 27      | Open Internship   | true           | Pass     | Open internships accepted            |
| 28      | Closed Internship | false          | Fail     | Closed internships rejected          |

**ECP Principle:** Testing one representative from each partition proves the entire class works. For CGPA < 6.0, testing 2.0 proves all values in that class fail consistently.

---

### Test Execution Results

```
[OK] Total Test Cases: 30
[OK] Passed: 30
[NO] Failed: 0
[OK] Success Rate: 100.0%
```

**Test Files:**

- `whitebox_tests.csv` - 15 white box test cases with detailed parameters
- `blackbox_tests.csv` - 15 black box test cases with BVA/ECP techniques

---

## User Manual

### System Requirements

- **Compiler:** GCC/G++ with C++11 support (or MSVC)
- **Operating System:** Windows, Linux, macOS
- **Runtime:** CLI terminal environment
- **Memory:** Minimal (~2-5 MB)

### Installation & Compilation

#### Step 1: Navigate to Project Directory

```bash
cd d:\projects\selab
```

#### Step 2: Compile the Source

```bash
g++ -o selab main.cpp
```

**Alternative compilers:**

```bash
# Using MSVC on Windows
cl main.cpp /Fe:selab.exe

# Using Clang
clang++ -o selab main.cpp
```

#### Step 3: Run the Application

```bash
# Windows
.\selab.exe

# Linux/macOS
./selab
```

### User Workflows

#### Portal 1: Student Portal

**Purpose:** Submit internship applications

**Workflow:**

1. Select "Student Portal" from main menu
2. Choose "Apply for Internship"
3. Enter Student ID, Internship ID, resume filename
4. System validates:
   - Student existence
   - CGPA eligibility
   - Application limit (max 5)
   - Internship open status
   - Resume non-empty
5. View application status

**Example Interaction:**

```
=== Student Portal ===
1. Apply for Internship
2. View My Status
3. Back to Main Menu
Enter choice: 1

Enter Student ID: 101
Enter Internship ID: 501
Enter resume file name: resume.pdf
Enter cover letter file name: coverletter.txt

Success
Updated Application Count: 1 / 5
```

#### Portal 2: HR/Faculty Portal

**Purpose:** Review and update application status

**Workflow:**

1. Select "HR / Faculty Portal"
2. Choose "Review Applications (HR)" or "Verify Completion (Faculty)"
3. View pending applications in table format
4. Update status: Pending -> Shortlisted -> Selected
5. Faculty mentor can verify selected applications

**Status Progression:**

```
Pending -> Shortlisted -> Selected -> Verified(Faculty)
```

#### Portal 3: System Testing

**Automatic Test Execution:**

- Program runs 30 pre-configured test cases on startup
- Tests verify:
  - All business rules enforcement
  - Edge cases and boundary conditions
  - Error handling
- Displays detailed test report with pass/fail status

---

## System Use Cases & Actors

The system supports four primary actors with their respective use cases:

```
ACTORS & USE CASES:

Student Actor:
  - Create Profile & Portfolio
  - Browse & Filter Internships
  - Apply for Internship

Company HR Actor:
  - Post Internship Listing
  - Review Applications & Schedule Interviews
  - Issue Certificate

Faculty Mentor Actor:
  - Review Weekly Reports
  - Verify Completion & NOC

Placement Officer Actor:
  - View Placement Analytics
  - Verify Completion & NOC
```

**Actor Responsibilities:**

| Actor                 | Role                  | Key Use Cases                                                         |
| --------------------- | --------------------- | --------------------------------------------------------------------- |
| **Student**           | Job applicant         | Search internships, apply, track status                               |
| **Company HR**        | Recruiter             | Post positions, review applications, conduct interviews, issue offers |
| **Faculty Mentor**    | Academic supervisor   | Monitor student progress, verify completion, approve NOC              |
| **Placement Officer** | Placement coordinator | Track analytics, verify all completions, coordinate with stakeholders |

---

## Developer Notes

### Technology Stack

| Component           | Technology           | Purpose                           |
| ------------------- | -------------------- | --------------------------------- |
| **Language**        | C++11                | Type-safe, high-performance       |
| **Data Structures** | `std::vector<T>`     | Dynamic arrays for entity storage |
| **Strings**         | `std::string`        | Dynamic string management         |
| **Architecture**    | EBC Pattern          | Separation of concerns            |
| **Testing**         | Structural (WBT/BBT) | Code and functionality validation |
| **Persistence**     | In-Memory (STL)      | No external database required     |

### File Structure

```
selab/
  main.cpp              # Boundary & Testing Layer (1200+ lines)
  controller.h          # Control Layer - Business Logic
  models.h              # Entity Layer - Data Models
  whitebox_tests.csv    # White Box Test Cases (15 cases)
  blackbox_tests.csv    # Black Box Test Cases (15 cases)
  selab.exe             # Compiled Executable
  README.md             # This file
```

### Data Persistence Strategy

**Current Implementation:** In-memory storage using STL containers

```cpp
// In-memory storage (no database)
std::vector<Student> studentStorage;
std::vector<Internship> internshipStorage;
std::vector<Application> applicationStorage;
```

**Advantages:**

- ✓ Rapid development and testing
- ✓ Zero external dependencies
- ✓ Academic focus on algorithms, not database administration

**Limitations:**

- ✗ Data lost on program exit (by design)
- ✗ Single-user/single-process only
- ✗ Not suitable for production systems

**Production Enhancement:** Replace STL vectors with:

- Persistent storage: SQLite, PostgreSQL
- REST API: Express.js/Flask backend
- Multi-user support: User authentication & authorization

### Code Quality Highlights

**1. Type Safety**

```cpp
// Strong typing prevents category errors
struct Student { int studentID; float cgpa; };
struct Internship { int internshipID; bool isOpened; };
```

**2. Encapsulation**

```cpp
// ApplicationManager (Control Layer)
class ApplicationManager {
private:
    std::vector<Student> students;          // Hidden from outside
    std::vector<Application> applications;  // Encapsulated data
public:
    bool submitApplication(...);            // Public interface
};
```

**3. Memory Safety**

```cpp
// Safe pointer operations with bounds checking
Student *findStudentByID(int id) {
    for(auto &s : studentStorage) {
        if(s.studentID == id) return &s;
    }
    return nullptr;  // Explicit null return
}
```

**4. STL Best Practices**

```cpp
// Efficient iteration
for(std::size_t idx = 0; idx < storage.size(); ++idx) { ... }

// String handling with automatic memory management
std::string resume = "file.pdf";  // No manual new/delete
```

### Extending the System

**Future Enhancements:**

1. **Database Integration**

   ```cpp
   // Replace in-memory storage with SQL queries
   SQLite::Database db("internships.db");
   std::vector<Student> students = db.query("SELECT * FROM students");
   ```

2. **File Persistence**

   ```cpp
   // Save/load data to CSV or JSON
   void saveApplications(const std::string &filename);
   void loadApplications(const std::string &filename);
   ```

3. **Authentication**

   ```cpp
   // User login system
   bool authenticate(const std::string &username, const std::string &password);
   ```

4. **Email Notifications**

   ```cpp
   // Notify students of application status changes
   void sendStatusEmail(int studentID, const std::string &status);
   ```

5. **Web Interface**
   - Frontend: React/Vue.js
   - Backend: REST API (Node.js/Python)
   - Database: PostgreSQL

### Testing & Debugging

**Run Test Suite:**

```bash
.\selab.exe
# Automatically executes 30 test cases
# Displays detailed report with pass/fail status
```

**Debugging with GDB:**

```bash
g++ -g -o selab main.cpp      # Compile with debug symbols
gdb ./selab                    # Launch debugger
(gdb) run                      # Run program
(gdb) break main              # Set breakpoint
(gdb) print variable          # Inspect variables
```

**Code Review Checklist:**

- ✓ All business rules implemented?
- ✓ All edge cases tested?
- ✓ Memory leaks checked (valgrind)?
- ✓ Input validation complete?
- ✓ Error messages user-friendly?

---

## Academic Learning Outcomes

Upon completing this project, students understand:

1. **Software Architecture**
   - Entity-Boundary-Control pattern
   - Separation of concerns
   - Layered architecture principles

2. **Structural Testing**
   - White box testing (statement, branch, path coverage)
   - Black box testing (BVA, ECP)
   - Test design and execution

3. **C++ Programming**
   - STL containers (vector, string)
   - Pointer operations and references
   - Object-oriented design

4. **Business Logic Implementation**
   - Constraint validation
   - State management
   - Workflow orchestration

---

## References

- **EBC Pattern:** Wirfs-Brock, R., & McKean, B. (2003). Object Design: Roles, Responsibilities, and Collaborations
- **Structural Testing:** Beizer, B. (1990). Software Testing Techniques (2nd ed.)
- **BVA/ECP:** ISTQB Certified Tester Syllabus
- **C++ STL:** cppreference.com, C++ Standard Library Documentation

---

## License & Attribution

**Project Type:** Academic Assignment (B.Tech Computer Engineering)  
**Institution:** VJTI, Mumbai  
**Year:** 2025-2026  
**Use Case:** Educational demonstration of software engineering principles

---

**Last Updated:** April 2026
**Status:** Complete & Tested [OK]
**All Tests Passing:** 30/30 [OK]
