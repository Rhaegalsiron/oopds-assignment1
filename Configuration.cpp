#include "Configuration.h"

Configuration::Configuration(string configurationFile)
{
    this->nameOfFile = configurationFile;
    this->parseFile(this->nameOfFile);
    cout << this->targetWords[0];
}

string Configuration::parseFile(const string filename)
{
    ifstream fileToRead(filename);
    if (!fileToRead.is_open())
    {
        cerr << "Error: Unable to open file: " << this->nameOfFile << endl;
        return "";
    }
    stringstream contentStream;
    string line;
    while (getline(fileToRead, line))
    {
        if (!line.empty())
            // contentStream << line << "\n";
            this->parseLine(line);
    }

    fileToRead.close();
    return contentStream.str();
}

void Configuration::parseLine(string line)
{

    if (line.find("M by N :") != string::npos)
    {
        size_t delimiterPosition = line.find(":");
        string dimensions = line.substr(delimiterPosition + 1, line.size());
        dimensions = this->trimString(dimensions);

        delimiterPosition = dimensions.find(" ");
        string xString = dimensions.substr(0, delimiterPosition);
        string yString = dimensions.substr(delimiterPosition + 1, dimensions.size());
        xString = this->trimString(xString);
        yString = this->trimString(yString);
        this->targetWords.push_back(xString);
        this->targetWords.push_back(yString);

        this->dimensionX = stoi(xString);
        this->dimensionY = stoi(yString);

        return;
    }
    if (line.find("steps:") != string::npos)
    {
        size_t startingPosition = line.find(":");
        string words = line.substr(startingPosition + 1, 20);
        string numOfSteps = this->trimString(words);
        this->simulationSteps = stoi(numOfSteps);
        return;
    }
    if (line.find("robots") != string::npos)
    {
        size_t startingPosition = line.find(":");
        string words = line.substr(startingPosition + 1, 20);
        string numOfRobots = this->trimString(words);
        this->robotCount = stoi(numOfRobots);
        return;
    }

    if (line.find("GenericRobot") != string::npos)
    {
        size_t startingPos = line.find("t");
        string robotParameters = line.substr(startingPos + 1, line.size());
        robotParameters = this->trimString(robotParameters);

        startingPos = robotParameters.find(" ");
        string robotName = robotParameters.substr(0, startingPos);
        string nextcolumn = robotParameters.substr(startingPos + 1, robotParameters.size());
        size_t spacePos = nextcolumn.find(" ");
        string initialPosX = nextcolumn.substr(0, spacePos);
        string initialPosY = nextcolumn.substr(spacePos + 1, nextcolumn.size());

        RobotParameters param;
        param.name = robotName;
        param.initialX = initialPosX.find("random") == string::npos ? stoi(initialPosX) : RANDOM_POSITION;
        param.initialY = initialPosY.find("random") == string::npos ? stoi(initialPosY) : RANDOM_POSITION;

        this->robotLists.push_back(param);
    }
    this->targetWords.push_back("unit declerations");
}

void Configuration::parsedWords()
{
    string t = this->parseFile(this->nameOfFile);
    if (this->parseFile(this->nameOfFile).find("M by N:") != string::npos)
    {
        size_t createPos = this->parseFile(this->nameOfFile).find("M by N:");
        this->targetWords.push_back("gay");
    }
}

string Configuration::trimString(string input)
{
    size_t start = input.find_first_not_of(" \t\n\r");
    if (start == string::npos)
        return "";
    size_t end = input.find_last_not_of(" \t\n\r");
    if (end == string::npos)
        return "";
    return input.substr(start, end - start + 1);
}