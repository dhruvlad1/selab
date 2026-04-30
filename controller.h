#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "models.h"
#include <string>
#include <vector>

class InternshipController {
public:
    std::vector<Student> studentStorage;
    std::vector<Internship> internshipStorage;
    std::vector<Application> applicationStorage;

    std::string applyForInternship(Student &s, Internship &i, std::string resume, std::string coverLetter) {
        (void)coverLetter;

        if (s.studentID <= 0) {
            return "Failure: Invalid student ID";
        } else if (i.internshipID <= 0) {
            return "Failure: Invalid internship ID";
        } else if (s.cgpa < i.minCgpa) {
            return "Failure: Student is not eligible due to CGPA";
        } else if (s.currentApplicationCount >= 5) {
            return "Failure: Application limit reached";
        } else if (!i.isOpened) {
            return "Failure: Internship is not open";
        } else if (resume.empty()) {
            return "Failure: Missing resume";
        } else {
            Application newApplication;
            newApplication.studentID = s.studentID;
            newApplication.internshipID = i.internshipID;
            newApplication.resume = resume;
            newApplication.status = "Pending";
            newApplication.facultyVerified = false;

            applicationStorage.push_back(newApplication);
            s.currentApplicationCount++;

            return "Success";
        }
    }

    std::string updateStatus(int studentID, int internshipID, std::string newStatus) {
        if (studentID <= 0) {
            return "Failure: Invalid student ID";
        } else if (internshipID <= 0) {
            return "Failure: Invalid internship ID";
        } else if (newStatus != "Shortlisted" && newStatus != "Selected") {
            return "Failure: Invalid status";
        } else {
            for (std::size_t idx = 0; idx < applicationStorage.size(); ++idx) {
                if (applicationStorage[idx].studentID == studentID &&
                    applicationStorage[idx].internshipID == internshipID) {
                    applicationStorage[idx].status = newStatus;
                    return "Success";
                }
            }
            return "Failure: Application not found";
        }
    }

    std::string verifyInternship(int studentID, int internshipID) {
        if (studentID <= 0) {
            return "Failure: Invalid student ID";
        } else if (internshipID <= 0) {
            return "Failure: Invalid internship ID";
        } else {
            for (std::size_t idx = 0; idx < applicationStorage.size(); ++idx) {
                if (applicationStorage[idx].studentID == studentID &&
                    applicationStorage[idx].internshipID == internshipID) {
                    applicationStorage[idx].facultyVerified = true;
                    applicationStorage[idx].status = "Verified";
                    return "Success";
                }
            }
            return "Failure: Application not found";
        }
    }
};

#endif  // CONTROLLER_H
