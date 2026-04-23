#include <iostream>
#include "XMLreader.h"
#include "MeetingPlanner.h"
#include "gtest/gtest.h"


int main() {
    MeetingPlanner planner;
    XMLreader reader;

    if (reader.readFile("Meeting.xml", planner)) {


        std::cout << "XML parser werkte succesvol!\n" << std::endl;

        planner.printAll();

        planner.Write_Output("output.txt");
    } else {
        std::cout << "Er waren fouten bij het inlezen van de XML." << std::endl;
    }

    planner.processMeetings();

    return 0;
}