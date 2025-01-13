#include <iostream>
#include <httplib.h>
#include <unordered_map>
#include <string>

using namespace std;

// Define the student structure
struct Student {
    string id;
    string name;
    string dob;
    string yearOfPassing;
    string phoneNumber;
    string feesStatus;
};

// HashMap to store student data
unordered_map<string, Student> studentDB;

void addStudent(const Student& student) {
    studentDB[student.id] = student;
}

Student* getStudent(const string& id) {
    if (studentDB.find(id) != studentDB.end()) {
        return &studentDB[id];
    }
    return nullptr;  // Student not found
}

int main() {
    httplib::Server server;

    // Endpoint to insert student details
    server.Post("/insert", [](const httplib::Request& req, httplib::Response& res) {
        string id = req.get_param_value("id");
        string name = req.get_param_value("name");
        string dob = req.get_param_value("dob");
        string yearOfPassing = req.get_param_value("yearOfPassing");
        string phoneNumber = req.get_param_value("phoneNumber");
        string feesStatus = req.get_param_value("feesStatus");

        Student student = {id, name, dob, yearOfPassing, phoneNumber, feesStatus};
        addStudent(student);

        res.set_content("Student added successfully", "text/plain");
    });

    // Endpoint to search student by ID
    server.Get("/search", [](const httplib::Request& req, httplib::Response& res) {
        string id = req.get_param_value("id");
        Student* student = getStudent(id);

        if (student != nullptr) {
            string result = "ID: " + student->id + "\nName: " + student->name + "\nDOB: " + student->dob +
                            "\nYear of Passing: " + student->yearOfPassing + "\nPhone: " + student->phoneNumber +
                            "\nFees Status: " + student->feesStatus;
            res.set_content(result, "text/plain");
        } else {
            res.set_content("Student not found", "text/plain");
        }
    });

    // Start server
    server.listen("localhost", 5500);

    return 0;
}
