#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <vector>

struct Student {
    int studentID;
    float cgpa;
    int currentApplicationCount;
    std::vector<std::string> skills;
};

struct Internship {
    int internshipID;
    std::string domain;
    bool isOpened;
    float minCgpa;
};

struct Application {
    int studentID;
    int internshipID;
    std::string resume;
    std::string status;
    bool facultyVerified;
};

#endif  // MODELS_H
