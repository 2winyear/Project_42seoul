/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 00:28:00 by seungyel          #+#    #+#             */
/*   Updated: 2022/03/06 01:46:50 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>

/*
////찾긴 찾았는데 파일에 asdfasdf 
asdf -> hi로 바꿀려고 하면 buffer안에 있는거가 다 바뀜.

1. txt 파일을 연다
2. .replace 파일을 연다
3. txt 파일에서 buffer만큼 가지고온다.
while(파일 끝일 경우)
    4. buffer에서 find를 이용해서 찾는다. find함수는 못찾을 경우 npos리턴함.
    5. 원하는 만큼 바꾼다.
6. txt 파일을 닫는다.
7. .replace 파일을 닫는다.
*/

int main(int argc, char *argv[])
{
    if (argc != 4 || std::strlen(argv[2]) == 0)
    {
        std::cout << "Command Not Formatted Well" 
        << "./replace [ File Name ] [ String1 for SRC ] [ String2 for DST ]" 
        << std::endl;
        return (1);
    }

    std::string OutFile = argv[1];
    OutFile.append(".replace");
    std::string buffer;

    std::ifstream fin(argv[1]);
    if (fin.fail())
    {
        std::cout << "Error : could not open file" << std::endl;
        return (1);
    }
    
    std::ofstream fout(OutFile);
    if (fout.fail())
    {
        std::cout << "Error : could not create file" << std::endl;
        fout.close();
        return (1);
    }

    while (fin.peek() != EOF)
    {
        std::getline(fin, buffer);
        size_t idx = buffer.find(argv[2]);
        if (idx != std::string::npos)
        {
            fout << buffer.substr(0, idx) << argv[3] << std::endl;
            buffer = buffer.substr(idx + std::strlen(argv[2]));
        }
        else
            fout << buffer << std::endl;
    }
    fin.close();
    fout.close();
    return (0);
}