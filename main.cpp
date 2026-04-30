#include "controller.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

void seedSystemData(InternshipController &controller) {
    controller.studentStorage.clear();
    controller.internshipStorage.clear();
    controller.applicationStorage.clear();

    Student s1;
    s1.studentID = 101;
    s1.cgpa = 8.2f;
    s1.currentApplicationCount = 0;
    s1.skills = {"C++", "SQL"};

    Student s2;
    s2.studentID = 102;
    s2.cgpa = 6.0f;
    s2.currentApplicationCount = 1;
    s2.skills = {"Java", "Web Dev"};

    Student s3;
    s3.studentID = 103;
    s3.cgpa = 5.7f;
    s3.currentApplicationCount = 4;
    s3.skills = {"Python", "ML"};

    Internship i1;
    i1.internshipID = 201;
    i1.domain = "Web Dev";
    i1.isOpened = true;
    i1.minCgpa = 6.0f;

    Internship i2;
    i2.internshipID = 202;
    i2.domain = "FinTech";
    i2.isOpened = false;
    i2.minCgpa = 6.5f;

    Internship i3;
    i3.internshipID = 203;
    i3.domain = "Data Engineering";
    i3.isOpened = true;
    i3.minCgpa = 7.0f;

    controller.studentStorage.push_back(s1);
    controller.studentStorage.push_back(s2);
    controller.studentStorage.push_back(s3);

    controller.internshipStorage.push_back(i1);
    controller.internshipStorage.push_back(i2);
    controller.internshipStorage.push_back(i3);
}

Student *findStudentByID(InternshipController &controller, int studentID) {
    for (std::size_t idx = 0; idx < controller.studentStorage.size(); ++idx) {
        if (controller.studentStorage[idx].studentID == studentID) {
            return &controller.studentStorage[idx];
        }
    }
    return nullptr;
}

Internship *findInternshipByID(InternshipController &controller, int internshipID) {
    for (std::size_t idx = 0; idx < controller.internshipStorage.size(); ++idx) {
        if (controller.internshipStorage[idx].internshipID == internshipID) {
            return &controller.internshipStorage[idx];
        }
    }
    return nullptr;
}

int gTotalTests = 0;
int gPassedTests = 0;
const int gIdW = 4;
const int gTypeW = 8;
const int gTargetW = 17;
const int gScenarioW = 24;
const int gExpectedW = 24;
const int gActualW = 24;
const int gStatusW = 6;
const int gTableWidth = 120;

std::vector<std::string> wrapText(const std::string &text, std::size_t width) {
    std::vector<std::string> lines;
    if (width == 0) {
        lines.push_back(text);
        return lines;
    }

    std::size_t pos = 0;
    while (pos < text.size()) {
        std::size_t len = (text.size() - pos < width) ? (text.size() - pos) : width;
        std::size_t breakPos = pos + len;

        if (breakPos < text.size() && text[breakPos] != ' ') {
            std::size_t lastSpace = text.rfind(' ', breakPos);
            if (lastSpace != std::string::npos && lastSpace >= pos) {
                breakPos = lastSpace;
            }
        }

        if (breakPos == pos) {
            breakPos = pos + len;
        }

        std::string line = text.substr(pos, breakPos - pos);
        while (!line.empty() && line[0] == ' ') {
            line.erase(0, 1);
        }
        lines.push_back(line);

        pos = breakPos;
        while (pos < text.size() && text[pos] == ' ') {
            ++pos;
        }
    }

    if (lines.empty()) {
        lines.push_back("");
    }
    return lines;
}

void executeTest(int id,
                 std::string type,
                 std::string coverageTarget,
                 std::string scenario,
                 std::string expected,
                 std::string actual) {
    const bool passed = (expected == actual);
    gTotalTests++;
    if (passed) {
        gPassedTests++;
    }

    std::vector<std::string> targetLines = wrapText(coverageTarget, static_cast<std::size_t>(gTargetW));
    std::vector<std::string> scenarioLines = wrapText(scenario, static_cast<std::size_t>(gScenarioW));
    std::vector<std::string> expectedLines = wrapText(expected, static_cast<std::size_t>(gExpectedW));
    std::vector<std::string> actualLines = wrapText(actual, static_cast<std::size_t>(gActualW));

    std::size_t maxLines = targetLines.size();
    if (scenarioLines.size() > maxLines) {
        maxLines = scenarioLines.size();
    }
    if (expectedLines.size() > maxLines) {
        maxLines = expectedLines.size();
    }
    if (actualLines.size() > maxLines) {
        maxLines = actualLines.size();
    }

    for (std::size_t row = 0; row < maxLines; ++row) {
        const std::string idCell = (row == 0) ? std::to_string(id) : "";
        const std::string typeCell = (row == 0) ? type : "";
        const std::string targetCell = (row < targetLines.size()) ? targetLines[row] : "";
        const std::string scenarioCell = (row < scenarioLines.size()) ? scenarioLines[row] : "";
        const std::string expectedCell = (row < expectedLines.size()) ? expectedLines[row] : "";
        const std::string actualCell = (row < actualLines.size()) ? actualLines[row] : "";
        
        std::string statusCell = "";
        if (row == 0) {
            if (passed) {
                statusCell = "\033[32m[PASS]\033[0m";
            } else {
                statusCell = "\033[31m[FAIL]\033[0m";
            }
        }

        std::cout << std::left << std::setw(gIdW) << idCell << " | "
                  << std::setw(gTypeW) << typeCell << " | "
                  << std::setw(gTargetW) << targetCell << " | "
                  << std::setw(gScenarioW) << scenarioCell << " | "
                  << std::setw(gExpectedW) << expectedCell << " | "
                  << std::setw(gActualW) << actualCell << " | "
                  << std::setw(12) << statusCell << '\n';
    }

    std::cout << std::string(gTableWidth, '-') << '\n';
}

void printTestTableHeader() {
    std::cout << "\033[1m\033[44m" << std::string(gTableWidth, ' ') << "\033[0m\n";
    std::cout << "\033[1m\033[44m" << std::left << std::setw(gIdW) << "ID" << " | "
              << std::setw(gTypeW) << "Type" << " | "
              << std::setw(gTargetW) << "Coverage Target" << " | "
              << std::setw(gScenarioW) << "Scenario" << " | "
              << std::setw(gExpectedW) << "Expected" << " | "
              << std::setw(gActualW) << "Actual" << " | "
              << std::setw(12) << "Status" << "\033[0m\n";
    std::cout << "\033[1m" << std::string(gTableWidth, '=') << "\033[0m\n";
}

void runAutomatedTests(InternshipController &ctrl) {
    InternshipController testCtrl;
    seedSystemData(testCtrl);
    testCtrl.applicationStorage.clear();
    (void)ctrl;

    gTotalTests = 0;
    gPassedTests = 0;

    std::cout << "\033[1m\n" << std::string(gTableWidth, '=') << "\033[0m\n";
    std::cout << "\033[1m\033[46m" << std::string(gTableWidth, ' ') << "\033[0m\n";
    std::cout << "\033[1m\033[46m  AUTOMATED TEST REPORT - INTERNSHIP MANAGEMENT SYSTEM  \033[0m\n";
    std::cout << "\033[1m\033[46m" << std::string(gTableWidth, ' ') << "\033[0m\n";
    std::cout << "\033[1m" << std::string(gTableWidth, '=') << "\033[0m\n\n";
    
    std::cout << "\033[1m\033[45m >> SECTION A: WHITE BOX TESTING (15 Test Cases) \033[0m\n\n";
    std::cout << "  [*] Coverage Path Map (applyForInternship):\n";
    std::cout << "    - P1: Invalid Student ID\n";
    std::cout << "    - P2: Invalid Internship ID\n";
    std::cout << "    - P3: CGPA Eligibility Check\n";
    std::cout << "    - P4: Application Limit Check (Max 5)\n";
    std::cout << "    - P5: Internship Status Check\n";
    std::cout << "    - P6: Resume Validation\n\n";
    printTestTableHeader();

    auto makeStudent = [](int studentID, float cgpa, int currentApplicationCount) {
        return Student{studentID, cgpa, currentApplicationCount, {}};
    };
    auto makeInternship = [](int internshipID, bool isOpened, float minCgpa) {
        return Internship{internshipID, "General", isOpened, minCgpa};
    };
    auto normalizeApplyResult = [](const std::string &raw) {
        if (raw == "Success") {
            return std::string("Pass: Success");
        }
        if (raw == "Failure: Invalid student ID" || raw == "Failure: Invalid internship ID") {
            return std::string("Fail: Invalid ID");
        }
        if (raw == "Failure: Student is not eligible due to CGPA") {
            return std::string("Fail: Low CGPA");
        }
        if (raw == "Failure: Application limit reached") {
            return std::string("Fail: Limit Reached (Max 5)");
        }
        if (raw == "Failure: Internship is not open") {
            return std::string("Fail: Internship Closed");
        }
        if (raw == "Failure: Missing resume") {
            return std::string("Fail: Missing Resume");
        }
        return std::string("Fail: Unexpected");
    };
    auto runWhiteBoxApplyCase = [&](int id,
                                    const std::string &coverageTarget,
                                    const std::string &scenario,
                                    const std::string &expected,
                                    Student s,
                                    Internship i,
                                    const std::string &resume) {
        testCtrl.applicationStorage.clear();
        const std::string rawActual = testCtrl.applyForInternship(s, i, resume, "coverLetter.txt");
        const std::string actual = normalizeApplyResult(rawActual);
        executeTest(id, "WhiteBox", coverageTarget, scenario, expected, actual);
    };

    // --- WHITE BOX TESTING: PATH & STATEMENT COVERAGE ---
    runWhiteBoxApplyCase(1, "Path 1 + Statement", "Valid Path: All Criteria Met", "Pass: Success",
                         makeStudent(101, 8.5f, 0), makeInternship(501, true, 6.0f), "res.pdf");
    runWhiteBoxApplyCase(2, "Path 2 + Student ID", "Invalid Student ID (0)", "Fail: Invalid ID",
                         makeStudent(0, 8.5f, 0), makeInternship(501, true, 6.0f), "res.pdf");
    runWhiteBoxApplyCase(3, "Path 3 + Internship ID", "Invalid Internship ID (-1)", "Fail: Invalid ID",
                         makeStudent(102, 8.5f, 0), makeInternship(-1, true, 6.0f), "res.pdf");
    runWhiteBoxApplyCase(4, "Path 4 + CGPA Branch", "Branch: CGPA 5.5 < Min 6.0", "Fail: Low CGPA",
                         makeStudent(103, 5.5f, 0), makeInternship(501, true, 6.0f), "res.pdf");
    runWhiteBoxApplyCase(5, "Path 5 + Limit Branch", "Branch: App Count = 5", "Fail: Limit Reached (Max 5)",
                         makeStudent(104, 8.0f, 5), makeInternship(501, true, 6.0f), "res.pdf");
    runWhiteBoxApplyCase(6, "Path 6 + Open Branch", "Branch: Internship Closed", "Fail: Internship Closed",
                         makeStudent(105, 8.0f, 0), makeInternship(502, false, 6.0f), "res.pdf");
    runWhiteBoxApplyCase(7, "Path 7 + Resume Branch", "Branch: Empty Resume String", "Fail: Missing Resume",
                         makeStudent(106, 8.0f, 0), makeInternship(501, true, 6.0f), "");
    runWhiteBoxApplyCase(8, "Path Combo", "Path: Valid Min CGPA (6.0)", "Pass: Success",
                         makeStudent(107, 6.0f, 0), makeInternship(501, true, 6.0f), "res.pdf");
    runWhiteBoxApplyCase(9, "Path Combo", "Path: Negative ID check", "Fail: Invalid ID",
                         makeStudent(-5, 8.0f, 0), makeInternship(501, true, 6.0f), "res.pdf");
    runWhiteBoxApplyCase(10, "Path Combo", "Path: Max CGPA (10.0)", "Pass: Success",
                         makeStudent(108, 10.0f, 0), makeInternship(501, true, 6.0f), "res.pdf");
    runWhiteBoxApplyCase(11, "Path Combo", "Path: App Count at 4", "Pass: Success",
                         makeStudent(109, 7.5f, 4), makeInternship(501, true, 6.0f), "res.pdf");
    runWhiteBoxApplyCase(12, "Path Combo", "Path: Closed Intern with High CGPA", "Fail: Internship Closed",
                         makeStudent(110, 9.5f, 0), makeInternship(503, false, 6.0f), "res.pdf");
    runWhiteBoxApplyCase(13, "Path Priority", "Path: Invalid Student ID + Closed Intern", "Fail: Invalid ID",
                         makeStudent(0, 8.5f, 0), makeInternship(503, false, 6.0f), "res.pdf");
    runWhiteBoxApplyCase(14, "Path Combo", "Path: Valid Student + Missing Resume", "Fail: Missing Resume",
                         makeStudent(111, 8.0f, 0), makeInternship(501, true, 6.0f), "");
    runWhiteBoxApplyCase(15, "Statement Recheck", "Path: Zero Application Count", "Pass: Success",
                         makeStudent(112, 7.0f, 0), makeInternship(501, true, 6.0f), "res.pdf");

    std::cout << "\n\033[1m\033[45m >> SECTION B: BLACK BOX TESTING (15 Test Cases) \033[0m\n\n";
    std::cout << "  [*] Testing Techniques:\n";
    std::cout << "    - BVA: Boundary Value Analysis\n";
    std::cout << "    - ECP: Equivalence Class Partitioning\n\n";
    printTestTableHeader();
    auto runBlackBoxApplyCase = [&](int id,
                                    const std::string &scenario,
                                    const std::string &expected,
                                    Student s,
                                    Internship i,
                                    const std::string &resume) {
        testCtrl.applicationStorage.clear();
        const std::string rawActual = testCtrl.applyForInternship(s, i, resume, "coverLetter.txt");
        const std::string actual = normalizeApplyResult(rawActual);
        executeTest(id, "BlackBox", "BVA/ECP", scenario, expected, actual);
    };

    // --- BLACK BOX TESTING: BVA & ECP ---
    runBlackBoxApplyCase(16, "BVA: CGPA 5.99 (Just Below)", "Fail: Low CGPA",
                         makeStudent(201, 5.99f, 0), makeInternship(501, true, 6.0f), "res.pdf");
    runBlackBoxApplyCase(17, "BVA: CGPA 6.00 (Exact Boundary)", "Pass: Success",
                         makeStudent(202, 6.00f, 0), makeInternship(501, true, 6.0f), "res.pdf");
    runBlackBoxApplyCase(18, "BVA: CGPA 6.01 (Just Above)", "Pass: Success",
                         makeStudent(203, 6.01f, 0), makeInternship(501, true, 6.0f), "res.pdf");

    runBlackBoxApplyCase(19, "BVA: App Count 4 (Below Limit)", "Pass: Success",
                         makeStudent(204, 7.5f, 4), makeInternship(501, true, 6.0f), "res.pdf");
    runBlackBoxApplyCase(20, "BVA: App Count 5 (At Limit)", "Fail: Limit Reached (Max 5)",
                         makeStudent(205, 7.5f, 5), makeInternship(501, true, 6.0f), "res.pdf");
    runBlackBoxApplyCase(21, "BVA: App Count 6 (Over Limit)", "Fail: Limit Reached (Max 5)",
                         makeStudent(206, 7.5f, 6), makeInternship(501, true, 6.0f), "res.pdf");

    runBlackBoxApplyCase(22, "ECP: Valid CGPA (8.5)", "Pass: Success",
                         makeStudent(207, 8.5f, 0), makeInternship(501, true, 6.0f), "res.pdf");
    runBlackBoxApplyCase(23, "ECP: Invalid CGPA (2.0)", "Fail: Low CGPA",
                         makeStudent(208, 2.0f, 0), makeInternship(501, true, 6.0f), "res.pdf");
    runBlackBoxApplyCase(24, "ECP: Out of Range CGPA (-1.0)", "Fail: Low CGPA",
                         makeStudent(209, -1.0f, 0), makeInternship(501, true, 6.0f), "res.pdf");

    runBlackBoxApplyCase(25, "ECP: Valid Resume String", "Pass: Success",
                         makeStudent(210, 8.0f, 0), makeInternship(501, true, 6.0f), "my_cv.pdf");
    runBlackBoxApplyCase(26, "ECP: Empty Resume String", "Fail: Missing Resume",
                         makeStudent(211, 8.0f, 0), makeInternship(501, true, 6.0f), "");

    runBlackBoxApplyCase(27, "ECP: Status Open (Valid)", "Pass: Success",
                         makeStudent(212, 8.0f, 0), makeInternship(501, true, 6.0f), "res.pdf");
    runBlackBoxApplyCase(28, "ECP: Status Closed (Invalid)", "Fail: Internship Closed",
                         makeStudent(213, 8.0f, 0), makeInternship(503, false, 6.0f), "res.pdf");

    runBlackBoxApplyCase(29, "BVA: Student ID 1 (Min Valid)", "Pass: Success",
                         makeStudent(1, 8.0f, 0), makeInternship(501, true, 6.0f), "res.pdf");
    runBlackBoxApplyCase(30, "BVA: Student ID 0 (Min Invalid)", "Fail: Invalid ID",
                         makeStudent(0, 8.0f, 0), makeInternship(501, true, 6.0f), "res.pdf");

    std::cout << "\033[1m" << std::string(120, '=') << "\033[0m\n\n";
    
    int failed = gTotalTests - gPassedTests;
    float passPercentage = (gTotalTests > 0) ? (gPassedTests * 100.0f / gTotalTests) : 0.0f;
    
    std::cout << "\033[1m\033[46m" << std::string(gTableWidth, ' ') << "\033[0m\n";
    std::cout << "\033[1m\033[46m  TEST EXECUTION SUMMARY  \033[0m\n";
    std::cout << "\033[1m\033[46m" << std::string(gTableWidth, ' ') << "\033[0m\n\n";
    
    std::cout << "  Total Test Cases Executed: " << "\033[1m" << gTotalTests << "\033[0m\n";
    std::cout << "  [+] Passed: " << "\033[32m\033[1m" << gPassedTests << "\033[0m\n";
    std::cout << "  [-] Failed: " << "\033[" << (failed > 0 ? "31" : "32") << "m\033[1m" << failed << "\033[0m\n";
    std::cout << "  Success Rate: " << "\033[33m\033[1m" << std::fixed << std::setprecision(1) << passPercentage << "%\033[0m\n\n";
    
    if (failed == 0) {
        std::cout << "\033[32m\033[1m  [SUCCESS] ALL TESTS PASSED SUCCESSFULLY! \033[0m\n\n";
    } else {
        std::cout << "\033[31m\033[1m  [ERROR] SOME TESTS FAILED. REVIEW DETAILS ABOVE. \033[0m\n\n";
    }
    
    std::cout << "\033[1m" << std::string(gTableWidth, '=') << "\033[0m\n\n";
}

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void pressEnterToContinue() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printApplicationTable(const InternshipController &controller) {
    if (controller.applicationStorage.empty()) {
        std::cout << "No applications available.\n";
        return;
    }

    std::cout << std::left << std::setw(6) << "Idx"
              << std::setw(12) << "StudentID"
              << std::setw(14) << "InternshipID"
              << std::setw(20) << "Resume"
              << std::setw(15) << "Status"
              << std::setw(10) << "Verified" << '\n';
    std::cout << std::string(77, '-') << '\n';

    for (std::size_t idx = 0; idx < controller.applicationStorage.size(); ++idx) {
        const Application &app = controller.applicationStorage[idx];
        std::cout << std::left << std::setw(6) << idx
                  << std::setw(12) << app.studentID
                  << std::setw(14) << app.internshipID
                  << std::setw(20) << app.resume
                  << std::setw(15) << app.status
                  << std::setw(10) << (app.facultyVerified ? "Yes" : "No") << '\n';
    }
}

void showStudentStatus(InternshipController &controller) {
    int studentID = 0;
    std::cout << "Enter Student ID: ";
    if (!(std::cin >> studentID)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid Student ID.\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Student *student = findStudentByID(controller, studentID);
    if (student == nullptr) {
        std::cout << "Student not found.\n";
        return;
    }

    std::cout << "\nStudent ID: " << student->studentID << '\n';
    std::cout << "Current Application Count: " << student->currentApplicationCount << " / 5\n";
    std::cout << std::left << std::setw(14) << "InternshipID"
              << std::setw(15) << "Status"
              << std::setw(10) << "Verified" << '\n';
    std::cout << std::string(39, '-') << '\n';

    bool found = false;
    for (std::size_t idx = 0; idx < controller.applicationStorage.size(); ++idx) {
        const Application &app = controller.applicationStorage[idx];
        if (app.studentID == studentID) {
            found = true;
            std::cout << std::left << std::setw(14) << app.internshipID
                      << std::setw(15) << app.status
                      << std::setw(10) << (app.facultyVerified ? "Yes" : "No") << '\n';
        }
    }

    if (!found) {
        std::cout << "No applications found for this student.\n";
    }
}

void handleStudentPortal(InternshipController &controller) {
    while (true) {
        clearScreen();
        std::cout << "=== Student Portal ===\n";
        std::cout << "1. Apply for Internship\n";
        std::cout << "2. View My Status\n";
        std::cout << "3. Back to Main Menu\n";
        std::cout << "Enter choice: ";

        int choice = 0;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            pressEnterToContinue();
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            int studentID = 0;
            int internshipID = 0;
            std::string resume;
            std::string coverLetter;

            std::cout << "Enter Student ID: ";
            if (!(std::cin >> studentID)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid Student ID.\n";
                pressEnterToContinue();
                continue;
            }

            std::cout << "Enter Internship ID: ";
            if (!(std::cin >> internshipID)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid Internship ID.\n";
                pressEnterToContinue();
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Enter resume file name: ";
            std::getline(std::cin, resume);
            std::cout << "Enter cover letter file name: ";
            std::getline(std::cin, coverLetter);

            Student *student = findStudentByID(controller, studentID);
            Internship *internship = findInternshipByID(controller, internshipID);

            if (student == nullptr) {
                std::cout << "Failure: Student not found in system\n";
            } else if (internship == nullptr) {
                std::cout << "Failure: Internship not found in system\n";
            } else {
                std::string result =
                    controller.applyForInternship(*student, *internship, resume, coverLetter);
                std::cout << result << '\n';
                std::cout << "Updated Application Count: " << student->currentApplicationCount << " / 5\n";
            }
            pressEnterToContinue();
        } else if (choice == 2) {
            showStudentStatus(controller);
            pressEnterToContinue();
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "Invalid choice. Try again.\n";
            pressEnterToContinue();
        }
    }
}

void handleHrFacultyPortal(InternshipController &controller) {
    while (true) {
        clearScreen();
        std::cout << "=== HR / Faculty Portal ===\n";
        std::cout << "1. Review Applications (HR)\n";
        std::cout << "2. Verify Completion (Faculty Mentor)\n";
        std::cout << "3. Back to Main Menu\n";
        std::cout << "Enter choice: ";

        int choice = 0;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            pressEnterToContinue();
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            std::cout << "\nCurrent Applications:\n";
            printApplicationTable(controller);

            if (controller.applicationStorage.empty()) {
                pressEnterToContinue();
                continue;
            }

            int appIndex = -1;
            std::cout << "\nEnter application index to review (-1 to skip): ";
            if (!(std::cin >> appIndex)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input.\n";
                pressEnterToContinue();
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (appIndex == -1) {
                pressEnterToContinue();
                continue;
            }
            if (appIndex < 0 || static_cast<std::size_t>(appIndex) >= controller.applicationStorage.size()) {
                std::cout << "Invalid application index.\n";
                pressEnterToContinue();
                continue;
            }

            std::string newStatus;
            std::cout << "Enter new status (Shortlisted/Selected): ";
            std::getline(std::cin, newStatus);

            Application &app = controller.applicationStorage[static_cast<std::size_t>(appIndex)];
            std::string result = controller.updateStatus(app.studentID, app.internshipID, newStatus);
            std::cout << result << '\n';
            pressEnterToContinue();
        } else if (choice == 2) {
            std::cout << "\nSelected Applications Eligible for Verification:\n";
            printApplicationTable(controller);

            if (controller.applicationStorage.empty()) {
                pressEnterToContinue();
                continue;
            }

            int appIndex = -1;
            std::cout << "\nEnter application index to verify (-1 to skip): ";
            if (!(std::cin >> appIndex)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input.\n";
                pressEnterToContinue();
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (appIndex == -1) {
                pressEnterToContinue();
                continue;
            }
            if (appIndex < 0 || static_cast<std::size_t>(appIndex) >= controller.applicationStorage.size()) {
                std::cout << "Invalid application index.\n";
                pressEnterToContinue();
                continue;
            }

            Application &app = controller.applicationStorage[static_cast<std::size_t>(appIndex)];
            if (app.status != "Selected") {
                std::cout << "Failure: Only Selected applications can be verified.\n";
                pressEnterToContinue();
                continue;
            }

            std::string result = controller.verifyInternship(app.studentID, app.internshipID);
            std::cout << result << '\n';
            pressEnterToContinue();
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "Invalid choice. Try again.\n";
            pressEnterToContinue();
        }
    }
}

int main() {
    InternshipController controller;
    seedSystemData(controller);
    clearScreen();
    runAutomatedTests(controller);
    return 0;
}
