#include <iostream>
#include <limits>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "clock.h"

enum class timePartType {
    HOUR,
    MINUTE,
    SECOND,
};

void clockTick(clockType &clockToTick, timePartType timePart = timePartType::SECOND);
bool codeGradeLoopFix();
clockType *makeClock();
bool validFormat(std::string format);
void resetStream();
bool validPart(std::string part);
bool validPositiveInt(int num);
int inputPositiveInt(std::string prompt, std::string err);

// Helper function to generate random clock data
clockType *generateRandomClock();

int main()
{
    srand(time(0));  // Initialize random seed

    clockType **c = nullptr;
    int numClocks = 0;

    numClocks = inputPositiveInt("How many clocks do you want to make? ", "Please enter a positive number of clocks!");
    if (numClocks == -999)
    {
        return 0;
    }

    c = new clockType *[numClocks];

    // Create random clocks directly
    for (int i = 0; i < numClocks; i++)
    {
        c[i] = generateRandomClock();  // Generate random clock
        if (c[i] == nullptr)
        {
            return 0;
        }
    }

    std::cout << "All of the clocks: " << std::endl;
    for (int i = 0; i < numClocks; i++)
    {
        std::cout << c[i]->tostring() << std::endl;
        delete c[i];
        c[i] = nullptr;
    }
    delete[] c;
    c = nullptr;

    return 0;
}

void clockTick(clockType &clockToTick, timePartType timePart)
{
    switch (timePart)
    {
    case timePartType::HOUR:
        clockToTick.incrementHours();
        break;
    case timePartType::MINUTE:
        clockToTick.incrementMinutes();
        break;
    case timePartType::SECOND:
    default:
        clockToTick.incrementSeconds();
        break;
    }
    std::cout << clockToTick.tostring() << std::endl;
}

bool codeGradeLoopFix()
{
    if (std::cin.eof())
    {
        std::cout << "Infinite loop detected. Out of input ending program." << std::endl;
        return true;
    }
    return false;
}

clockType *generateRandomClock()
{
    int formatChoice = rand() % 2;  // Randomize between 12-hour or 24-hour format
    int hour = rand() % (formatChoice == 0 ? 12 : 24); // Randomize hour based on clock format
    int minute = rand() % 60; // Randomize minute
    int second = rand() % 60; // Randomize second
    std::string part = (formatChoice == 0 && rand() % 2 == 0) ? "AM" : "PM"; // Randomize AM/PM for 12-hour clock

    clockType *newClock = nullptr;

    if (formatChoice == 0) // 12-hour clock
    {
        newClock = new twelveHrClock(hour, minute, second, part == "AM" ? AM : PM);
        std::cout << newClock->tostring() << std::endl;
    }
    else // 24-hour clock
    {
        newClock = new twentyFourHrClock(hour, minute, second);
        std::cout << newClock->tostring() << std::endl;
    }
    return newClock;
}

bool validFormat(std::string format)
{
    std::transform(format.begin(), format.end(), format.begin(), ::tolower);

    for (int i = 0; i < 2; i++)
    {
        if (clockType::formatToStr[i] == format)
            return true;
    }
    return false;
}

void resetStream()
{
    std::cout << "You entered something that is not a number." << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool validPart(std::string part)
{
    std::transform(part.begin(), part.end(), part.begin(), ::toupper);

    for (int i = 0; i < 2; i++)
    {
        if (part == clockType::partToStr[i])
        {
            return true;
        }
    }
    return false;
}

bool validPositiveInt(int num)
{
    return num > 0;
}

int inputPositiveInt(std::string prompt, std::string err)
{
    int input;
    std::cout << prompt;
    std::cin >> input;
    while (!std::cin || !validPositiveInt(input))
    {
        if (codeGradeLoopFix())
        {
            return -999;
        }
        if (!std::cin)
        {
            resetStream();
        }
        std::cout << err << std::endl;
        std::cout << prompt;
        std::cin >> input;
    }
    return input;
}
