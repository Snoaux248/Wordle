//
//  Wordle.cpp
//  h
//
//  Created by Nolan Jones on 12/31/23.
//

#include "Wordle.hpp"
#include <string>
#include <sstream>
inline std::string color(int color){
    std::ostringstream os;
    if(color == 0){
        os << "\e[0m";
    }else if(color == 1){
        os << "\e[42m";
    }else if(color == 2){
        os << "\e[43m";
    }else if(color == 3){
        os << "\e[31m";
    }
    return os.str();
}


std::ostream& green(std::ostream& os){
    return os << "\e[42m";
}

std::ostream& yellow(std::ostream& os){
    return os << "\e[43m";
}

std::ostream& red(std::ostream& os){
    return os << "\e[31m";
}

std::ostream& style_off(std::ostream& os){
    return os << "\e[0m";
}

std::string input_array[5] = {"ampyx", "blink", "fjord", "swung", "vetch" };

struct pixel{
    char c = '_';
    int style = 0;
};

pixel Wordle_screen[5][6];
pixel Found[26] = {'q',0, 'w',0, 'e',0, 'r',0, 't',0, 'y',0, 'u',0, 'i',0, 'o',0, 'p',0, 'a',0, 's',0, 'd',0, 'f',0, 'g',0, 'h',0, 'j',0, 'k',0, 'l',0, 'z',0, 'x',0, 'c',0, 'v',0, 'b',0, 'n',0, 'm',0, };

void update_screen(int row, int column, char c, int style){
    Wordle_screen[column][row] = {c, style};
}

void update_kb(char c, int style){
    for(int i = 0; i < 26; i++){
        if(Found[i].c == c && Found[i].style != 2){
            Found[i].style = style;
            break;
        }
    }
}

void display_screen(){
    for(int i = 0; i < 6; i++){
        std::cout<< "     ";
        for(int j = 0; j < 5; j++){
            if(Wordle_screen[j][i].style == 2){
                std::cout << green << Wordle_screen[j][i].c << style_off << " ";
            }else if(Wordle_screen[j][i].style == 0){
                std::cout << Wordle_screen[j][i].c << " ";
            }else if(Wordle_screen[j][i].style == 1){
                std::cout << yellow << Wordle_screen[j][i].c << style_off << " ";
            }
        }
        std::cout << std::endl;
    }
    
    
    std::cout << "___________________" << std::endl;
    for(int i = 0; i < 26; i++){
        if(Found[i].style == 2){
            std::cout << green << Found[i].c << style_off << " ";
        }else if(Found[i].style == 0){
            std::cout << Found[i].c << " ";
        }else if(Found[i].style == 1){
            std::cout << yellow << Found[i].c << style_off <<" ";
        }else if(Found[i].style == 3){
            std::cout << red << Found[i].c << style_off <<" ";
        }
        if(i == 9 || i == 18 || i == 25){
            std::cout << std::endl;
        }
        if(i == 9){
            std::cout << " ";
        }
        if(i == 18){
            std::cout << "  ";
        }
    }
    std::cout << std::endl;
}

//
bool contains(std::string solution, char c){
    bool ct = false;
    for(int i = 0; i < 5; i++){
        if(solution.at(i) == c){
            ct = true;
            break;
        }
    }
    return ct;
}


std::vector<std::string> dictionary;
std::vector<std::string> dictionary_to_test;
std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

bool test_against(std::string input, std::string solution, int row){
    if(input == solution){
        for(int i = 0; i < 5; i++){
            update_screen(row, i, input.at(i), 2);
            update_kb(input.at(i), 2);
        }
        return true;
    }else{
        for(int i = 0; i < 5; i++){
            if(contains(solution, input.at(i)) == true){
                if(solution.at(i) == input.at(i)){
                    update_screen(row, i, input.at(i), 2);
                    update_kb(input.at(i), 2);
                }else{
                    update_screen(row, i, input.at(i), 1);
                    update_kb(input.at(i), 1);
                }
            }else{
                update_screen(row, i, input.at(i), 0);
                update_kb(input.at(i), 3);
            }
            
        }
        return false;
    }
    
    return false;
}

bool test_against2(std::string input, std::string solution, int row){
    if(input == solution){
        for(int i = 0; i < 5; i++){
            update_screen(row, i, input.at(i), 2);
        }
        return true;
    }else{
        for(int i = 0; i < 5; i++){
            if(contains(solution, input.at(i)) == true){
                if(solution.at(i) == input.at(i)){
      
                }else{
                    
                }
            }else{
               
            }
            
        }
        return false;
    }
    
    return false;
}
/*
int test_if_word(range index, std::string input){
    
    for(int i = 1; i < input.length(); i++){
        bool catch1 = false;
        bool catch2 = false;
        range new_index;
        std::cout << i << std::endl;
        std::cout << index.r1 << " " << index.r2 << std::endl;
        for(int j = index.r1; j <= index.r2; j++){
            std::cout << dictionary_to_test[j] << std::endl;
            if(dictionary_to_test[j].at(i) == input.at(i) && catch1 == false){
                catch1 = true;
                new_index.r1 = j;
            }else if(dictionary_to_test[j].at(i) != input.at(i) && catch1 == true){
                new_index.r2 = j - 1;
                catch2 = true;
                break;
            }
        }
        if(catch1 == false){
            std::cout << "word does not exist" << std::endl;
            return 0;
        }else if(catch1 == true && catch2 == false){
            index.r1 = new_index.r1;
            if(new_index.r1 == index.r2){//word exists
                return 1;
            }
            
        }else if(catch1 == true && catch2 == true){
            index = new_index;
            if(i == 4 && new_index.r1 == new_index.r2){
                return 1;
            }
        }
    }
        
    return 2;
}*/
bool allready_used(int run, std::string input){
    for(int r = 0; r < 6; r++){
        for(int c = 0; c < 5; c++){
            if(input.at(c) == Wordle_screen[c][r].c && c == 4){
                std::cout << "word has allready been used" << std::endl;
                return true;
            }else if(input.at(c) != Wordle_screen[c][r].c){
                break;
            }
        }
    }
    return false;
}

int test_if_word(std::string input){
    long int x = 0;
    while(x < dictionary_to_test.size()){
        for(int i = 1; i < 5; i++){
            //std::cout << dictionary_to_test[x] << std::endl;
            if(dictionary_to_test[x].at(i) != input.at(i)){
                break;
            }else if(i == 4 && dictionary_to_test[x].at(i) == input.at(i)){
                return 1;
            }
        }
        x++;
    }
    return 0;
}

std::string get_user_input(int run){
    bool still_getting {true};
    std::string input = "";
    do{
        std::cout << "Please type in your guess: ";
        getline(std::cin, input);
        if(input.length() != 5){
            std::cout << "Invalid word Length!" << std::endl;
        }else{
            still_getting = allready_used(run, input);
            //usleep(9000000);
            //std::cout << "why" << std::endl;
        }
    }while(still_getting == true);
    
    return input;
}

bool rerun(){
    bool finaly = false;
    std::string choice = "Y";
    
    do{
        std::cout << "would you like to play again?(Y/N): ";
        getline(std::cin, choice);
        char c = choice.at(0);
        if(tolower(c) == 'n'){
            finaly = true;
            return false;
        }else if(tolower(c) == 'y'){
            finaly = true;
            
            for(int i = 0; i < 6; i++){
                for(int j = 0; j < 5; j++){
                    Wordle_screen[j][i] = {'_', 0};
                }
            }
            for(int i = 0; i < 26; i ++){
                Found[i].style = 0;
            }
            return true;
        }
        
    }while(finaly == false);
    
    return 0;
}
void Wordle(){
    
    //readFile
    std::string file_to_open = "/Wordle/organize.csv";
    std::ifstream inFS;
    
    inFS.open(file_to_open);
    if(inFS.fail()){
        std::cout << "failed to open: " + file_to_open << std::endl;
        exit(1);
    }
    
    std::string line;
    int length = 0;
    while(!inFS.eof()){
        getline(inFS, line, '\n');
        dictionary.push_back(line);
        line = "";
        length++;
    }
    inFS.close();
    
    bool crazy = true;
    
    do{
        srand(static_cast<int>(time(NULL)));
        
        int word_index = rand() % length;
        std::string solution = dictionary[word_index];
        
        //send into an array;
        int turn = 0;
        bool game {true};
        std::string input;
        
        system("clear");
        //std::cout << solution << std::endl;
        display_screen();
        
        do{
            
            dictionary_to_test.clear();
            /*
            if(turn < 5){
                input = input_array[turn];
            }else{
                input = get_user_input(turn);
            }*/
            
            input = get_user_input(turn);
            char c = input.at(0);
            
            std::ifstream inFS;
            std::string file_to_open = "/Wordle/dictionary_";
            file_to_open.push_back(c);
            file_to_open.append(".csv");
            
            inFS.open(file_to_open);
            if(inFS.fail()){
                std::cout << "failed to open: " + file_to_open << std::endl;
                exit(2);
            }
            
            int count = -1;
            while(!inFS.eof()){
                getline(inFS, line, '\n');
                dictionary_to_test.push_back(line);
                line = "";
                count++;
            }
            inFS.close();
            
            int x = test_if_word(input);
            if(x == 0){
                
                std::cout << "word is invalid" << std::endl;
            }else if(x == 1){
         
                system("clear");
                bool win = test_against(input, solution, turn);
                
                
                if(win == true){
                    
                    std::cout << "you have won the word is:" + solution << std::endl;
                    //std::cout << solution << std::endl;
                    display_screen();
                    game = false;
                    crazy = rerun();
                    
                }else{
                    
                    if(turn == 5){
                        
                        std::cout << "you have lost, the word was : " + solution << std::endl;
                        //std::cout << solution << std::endl;
                        display_screen();
                        game = false;
                        crazy = rerun();
                    }else{
                        
                        turn++;
                        //std::cout << solution << std::endl;
                        display_screen();
                        
                    }
                }
                
                
            }
        }while(game == true);
        
    }while(crazy == true);
}
