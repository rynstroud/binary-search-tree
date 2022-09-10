//
//  main.cpp
//  Lab 08 BST
//
//  Created by C/R

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "BST.h"

int main(int argc, const char * argv[])
{
    //Checking for correct number of arguments
    if (argc < 3)
    {
        std::cerr << "Please provide the name of input and output files, thanks\n";
        return 1;
    }
       
    //Checking if input file opens
    std::ifstream in(argv[1]);
    if (!in)
    {
        std::cerr << "Failure to open input file: " << argv[1] << std::endl;
        return 2;
    }
       
    //Checking if output file opens
    std::ofstream out(argv[2]);
    if (!out)
    {
        in.close();
        std::cerr << "Failure to open output file: " << argv[1] << std::endl;
        return 3;
    }
    
    BST<int> intSearchTree;
    BST<std::string> stringSearchTree;
    int valComm = -1;
    bool works = false;
    
    for (std::string line; getline(in, line);)
    {
        std::string command = "";
        std::istringstream iss(line);
        iss >> command;
        if (command == "print") out << command << ":";
        else out << command << " ";
        
        try
        {
            if (command == "INT")
            {
                valComm = 1;
                out << " true" << std::endl;
            }
            else if (command == "STRING")
            {
                valComm = 0;
                out << " true" << std::endl;
            }
            else if (command == "add")
            {
                if (valComm == 0)
                {
                    std::string newSNode;
                    iss >> newSNode;
                    out << newSNode;
                    works = stringSearchTree.addNode(newSNode);
                    if (works) out << " true" << std::endl;
                    else out << " false" << std::endl;
                }
                else if (valComm == 1)
                {
                    int newINode;
                    iss >> newINode;
                    out << newINode;
                    works = intSearchTree.addNode(newINode);
                    if (works) out << " true" << std::endl;
                    else out << " false" << std::endl;
                }
                else throw std::string("**Error: no object created");
            }
            else if (command == "remove")
            {
                if (valComm == 0)
                {
                    std::string oldSNode;
                    iss >> oldSNode;
                    out << oldSNode;
                    works = stringSearchTree.removeNode(oldSNode);
                    if (works) out << " true" << std::endl;
                    else out << " false" << std::endl;
                }
                else if (valComm == 1)
                {
                    int oldINode;
                    iss >> oldINode;
                    out << oldINode;
                    works = intSearchTree.removeNode(oldINode);
                    if (works) out << " true" << std::endl;
                    else out << " false" << std::endl;
                }
                else throw std::string("**Error: no object created");
            }
            else if (command == "clear")
            {
                if (valComm == 0)
                {
                    works = stringSearchTree.clearTree();
                    if (works) out << "true" << std::endl;
                    else out << "false" << std::endl;
                }
                else if (valComm == 1)
                {
                    works = intSearchTree.clearTree();
                    if (works) out << "true" << std::endl;
                    else out << "false" << std::endl;
                }
                else throw std::string("**Error: no object created");
            }
            else if (command == "size")
            {
                if (valComm == 0) out << stringSearchTree.size() << std::endl;
                else if (valComm == 1) out << intSearchTree.size() << std::endl;
                else throw std::string("**Error: no object created");
            }
            else if (command == "print")
            {
                if (valComm == 0)
                {
                    if (stringSearchTree.size() == 0) out << " empty\n";
                    else out << stringSearchTree.toString() << std::endl;
                }
                else if (valComm == 1)
                {
                    if (intSearchTree.size() == 0) out << " empty\n";
                    else out << intSearchTree.toString() << std::endl;
                }
                else throw std::string("**Error: no object created");
            }
            else if (command == "find")
            {
               if (valComm == 0)
                {
                    std::string fSNode;
                    iss >> fSNode;
                    out << fSNode;
                    works = stringSearchTree.find(fSNode);
                    if (works) out << " found" << std::endl;
                    else out << " not found" << std::endl;
                }
                else if (valComm == 1)
                {
                    int fINode;
                    iss >> fINode;
                    out << fINode;
                    works = intSearchTree.find(fINode);
                    if (works) out << " found" << std::endl;
                    else out << " not found" << std::endl;
                }
                else throw std::string("**Error: no object created");
            }
            else
            {
                throw std::string("**Error: " + line);
            }
            
        } catch(std::string errorString)
        {
            out <<  errorString << std::endl;
        }
    }
    
    
    return 0;
}
