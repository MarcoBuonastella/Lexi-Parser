#include <iostream>
#include <map>
#include <algorithm>
#include <utility>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

std::string printToken(std::string token, std::string lexeme){
  if(token == "ID"){
    if(lexeme == "int"){
      //std::cout << "here" <<std::endl;
      return "INT";
    }
    if(lexeme == "if"){
      return "IF";
    }
    if(lexeme == "else"){
      return "ELSE";
    }
    if(lexeme == "while"){
      return "WHILE";
    }    
    if(lexeme == "return"){
      return "RETURN";
    }
  }
  if(token == "ZERO"){
    return "NUM";
  }
  else{
    return "ID";
  }
}

int main(){

  //set up DFA

  std::map<std::pair<std::string,std::string>,std::string> transFunc;
  //vector <std::string> states = {};  
  vector<std::string> finalStates = {};
  vector<std::string> alphabet = {};
  vector<std::string> letters = {};
  vector<std::string> digits = {};
  vector<std::string> group1 = {"ID","NUM", "RETURN", "IF", "ELSE", "WHILE", "INT", "ZERO"};
  vector<std::string> group2 = {"EQ","NE", "LT", "LE", "GT", "GE", "BECOMES"};

  for(int i = 97; i <= 122; i++){
    std::string s(1, char(i));
    letters.push_back(s);
    alphabet.push_back(s);
  }

  for(int i = 65; i <= 90; i++){
    std::string s(1, char(i));
    letters.push_back(s);
    alphabet.push_back(s);
  }

  for(int i = 48; i <= 57; i++){
    std::string s(1, char(i));
    digits.push_back(s);
    alphabet.push_back(s);
  }

  alphabet.push_back("(");
  alphabet.push_back(")");
  alphabet.push_back("{");
  alphabet.push_back("}");
  alphabet.push_back("=");
  alphabet.push_back("!");
  alphabet.push_back("<");
  alphabet.push_back(">");
  alphabet.push_back("+");
  alphabet.push_back("-");
  alphabet.push_back("*");
  alphabet.push_back("/");
  alphabet.push_back("%");
  alphabet.push_back(",");
  alphabet.push_back(";");
  alphabet.push_back(std::string(1,char(32)));
  alphabet.push_back(std::string(1,char(9)));
  alphabet.push_back(std::string(1,char(10)));
 
 transFunc.emplace(std::pair<std::string,std::string>("start",std::string(1,char(32))),"start");
  transFunc.emplace(std::pair<std::string,std::string>("start",std::string(1,char(9))),"start");
  transFunc.emplace(std::pair<std::string,std::string>("start",std::string(1,char(10))),"start");
  //transFunc.emplace(std::pair<std::string,std::string>("WS",std::string(1,char(32))),"start");
  //transFunc.emplace(std::pair<std::string,std::string>("WS",std::string(1,char(9))),"start");
  //transFunc.emplace(std::pair<std::string,std::string>("WS",std::string(1,char(10))),"WS");
  transFunc.emplace(std::pair<std::string,std::string>("start","("),"LPAREN");
  transFunc.emplace(std::pair<std::string,std::string>("start",")"),"RPAREN");
  transFunc.emplace(std::pair<std::string,std::string>("start","{"),"LBRACE");
  transFunc.emplace(std::pair<std::string,std::string>("start","}"),"RBRACE");
  transFunc.emplace(std::pair<std::string,std::string>("start","="),"BECOMES");
  transFunc.emplace(std::pair<std::string,std::string>("BECOMES","="),"EQ");
  transFunc.emplace(std::pair<std::string,std::string>("start","!"),"NOT");
  transFunc.emplace(std::pair<std::string,std::string>("NOT","="),"NE");
  transFunc.emplace(std::pair<std::string,std::string>("start","<"),"LT");
  transFunc.emplace(std::pair<std::string,std::string>("LT","="),"LE");
  transFunc.emplace(std::pair<std::string,std::string>("start",">"),"GT");
  transFunc.emplace(std::pair<std::string,std::string>("GT","="),"GE");
  transFunc.emplace(std::pair<std::string,std::string>("start","+"),"PLUS");
  transFunc.emplace(std::pair<std::string,std::string>("start","-"),"MINUS");
  transFunc.emplace(std::pair<std::string,std::string>("start","*"),"STAR");
  transFunc.emplace(std::pair<std::string,std::string>("start","/"),"SLASH");
  transFunc.emplace(std::pair<std::string,std::string>("SLASH","/"),"COMMENT");
  transFunc.emplace(std::pair<std::string,std::string>("start","%"),"PCT");
  transFunc.emplace(std::pair<std::string,std::string>("start",","),"COMMA");
  transFunc.emplace(std::pair<std::string,std::string>("start",";"),"SEMI");
  
  for(std::string letter:letters){
    transFunc.emplace(std::pair<std::string,std::string>("start",letter),"ID");
  }
  
  for(std::string letter:letters){
      transFunc.emplace(std::pair<std::string,std::string>("ID",letter),"ID");
  }

  for(std::string digit:digits){
      transFunc.emplace(std::pair<std::string,std::string>("ID",digit),"ID");
  }

  for(std::string digit:digits){
      if(digit!= "0"){
        transFunc.emplace(std::pair<std::string,std::string>("start",digit),"NUM");
      }
      else{
        transFunc.emplace(std::pair<std::string,std::string>("start",digit),"ZERO");
      }
  }

  for(std::string digit:digits){
      transFunc.emplace(std::pair<std::string,std::string>("NUM",digit),"NUM");
  }

  for(auto key: transFunc){
    if(!(std::find(finalStates.begin(), finalStates.end(), key.second) != finalStates.end())) {
      if(key.second!= "NOT" && key.second!= "COMMENT" && key.second!= "WS"){
        finalStates.push_back(key.second);
      }
    }
  }

std::string input;
std::string currState;
std::string lexeme;
bool comment = false;
bool whitespace = false;
while(std::getline(cin,input)){
    currState = "start";
    lexeme = "";
    for(int j = 0; j < input.length(); j++){
      std::string s(1,input[j]);
      if(currState != "start"){
      //std::cout << "CurrState: " << currState << " " << "| Symbol s: " << s << std::endl;
      }
      if(transFunc.count(std::pair<std::string,std::string>(currState,s)) > 0){
        currState = transFunc[std::pair<std::string,std::string>(currState,s)];
        if(currState == "COMMENT"){
          currState = "start";
          lexeme = "";
          break;
        }
        if(currState!= "start"){
          lexeme += s;
        }
      }
      else{
        std::string i;
        if(transFunc.count(std::pair<std::string,std::string>("start",s)) > 0){
        i = transFunc[std::pair<std::string,std::string>("start",s)];
        }
        if(!(std::find(finalStates.begin(), finalStates.end(), currState) != finalStates.end()) || (!(std::find(alphabet.begin(), alphabet.end(), s) != alphabet.end()))){
          std::cerr << "ERROR:" << "state: " << currState << " lexeme: " + lexeme << " s: " << s<<std::endl;
            return 0;
        }
        if((std::find(group1.begin(), group1.end(), i) != group1.end()) && (std::find(group1.begin(), group1.end(), currState) != group1.end())){
           std::cerr << "ERROR:" << "state: " << currState << " lexeme: " + lexeme << " s: " << s<<std::endl;
           return 0;
        }

        if((std::find(group2.begin(), group2.end(), i) != group2.end()) && (std::find(group2.begin(), group2.end(), currState) != group2.end())){
           std::cerr << "ERROR:" << "state: " << currState << " lexeme: " + lexeme << " s: " << s<<std::endl;
           return 0;
        }
        /*if((currState == "NUM" || currState == "ZERO") && (std::find(letters.begin(), letters.end(), s) != letters.end())){
          std::cerr << "ERROR:" << "state: " << currState << " lexeme: " + lexeme << " s: " << s<<std::endl;
          return 0;
        }
        if(currState == "LT" && s == "<"){          std::cerr << "ERROR:" << "state: " << currState << " lexeme: " + lexeme << " s: " << s<<std::endl;
          return 0;
        }

        if(currState == "LE" && s == "="){         std::cerr << "ERROR:" << "state: " << currState << " lexeme: " + lexeme << " s: " << s<<std::endl;
          return 0;
        }*/
        if(currState!= "start"){
          if(currState == "ID" || currState == "ZERO"){
            currState = printToken(currState, lexeme);
          }
          std::cout << currState << " " << lexeme << std::endl;
          currState = "start";
          lexeme = "";
          j--;
        }
      }
    }
    if(currState!= "start" && std::find(finalStates.begin(), finalStates.end(), currState) != finalStates.end()){
      if(currState == "ID" || currState == "ZERO"){
        currState = printToken(currState, lexeme);
      }
      std::cout << currState << " " << lexeme << std::endl;
    }
  }
return 0;
}

/*std::string input;
std::string lexeme;
std::string currState = "start";
bool comment = false;
bool breakUntilNewLine = false;
while(std::cin.get(input)){
  if(input == "\n"){
    breakUntilNewLine = false;
  }
  if(breakUntilNewLine){}
  else{
  currState = "start";
  lexeme = "";
  comment = false;
  std::cout << "input: " << input <<std::endl;
  for(int i = 0; i < input.length(); i++){
    std::string s(1,input[i]);
    std::cout << "CurrState: " << currState << " " << "| Symbol s: " << s << std::endl;
    //std::cout << transFunc[std::pair<std::string,std::string>(currState,s)] << std::endl;
    if(transFunc.count(std::pair<std::string,std::string>(currState,s)) > 0){
      currState = transFunc[std::pair<std::string,std::string>(currState,s)];
      if(currState == "COMMENT"){
        comment = true;
        breakUntilNewLine = true;
        break;
      }
      lexeme += s;
    }
    else{
      if(!(std::find(finalStates.begin(), finalStates.end(), currState) != finalStates.end())){
        //std::cout << "ERROR0: " << "state: " << currState << " lexeme: " + lexeme << " s: " << s<<std::endl;
        if(comment){
          //std::string j;
          //std::getline(cin,j);
          //std::cout << j <<std::endl;
          //break;
        }
        else{
          std::cerr << "ERROR:" << "state: " << currState << " lexeme: " + lexeme << " s: " << s<<std::endl;
          return 0;
        }
      }
      if(currState == "ID" || currState == "ZERO"){
        currState = printToken(currState, lexeme);
      }
      std::cout << currState << " " << lexeme << std::endl;
      currState = "start";
      lexeme = "";
      i--;
    }
  }
  if(!(std::find(finalStates.begin(), finalStates.end(), currState) != finalStates.end())){
    if(!comment){
      std::cerr << "ERROR:" << "state: " << currState << " lexeme: " + lexeme <<std::endl;
      return 0;
    }
  }
  if(currState == "ID" || currState == "ZERO"){
    currState = printToken(currState, lexeme);
  }
  std::cout << currState << " " << lexeme << std::endl;
}
}

  return 0;
}*/
