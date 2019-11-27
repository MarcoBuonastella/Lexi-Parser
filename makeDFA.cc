#include <iostream>
#include <map>
#include <algorithm>
#include <utility>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


  /*bool isAccepting(vector<std::string> finishStates, std::string state){
    for(std::string currState: finishStates){
      if(state == currState){
        return true;
      }
    }
    return false;
  }*/

int main(){
  std::map<std::pair<std::string,std::string>,std::string> transFunc;
  vector <std::string> states = {};  
  vector<std::string> finalStates = {};
  vector<std::string> alphabet = {};
  vector<std::string> letters = {};
  vector<std::string> digits = {};
  std::string input;

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
  //alphabet.push_back(std::string(1,char(32)));
  //alphabet.push_back(std::string(1,char(9)));
  //alphabet.push_back(std::string(1,char(10)));


   
  states.push_back("start");
  states.push_back("ID");
  states.push_back("NUM");
  states.push_back("ZERO");
  states.push_back("LPAREN");
  states.push_back("RPAREN");
  states.push_back("LBRACE");
  states.push_back("RBRACE");
  /*states.push_back("RETURN");
  states.push_back("IF");
  states.push_back("ELSE");
  states.push_back("WHILE");
  states.push_back("INT");*/
  states.push_back("BECOMES");
  states.push_back("EQ");
  states.push_back("NOT");
  states.push_back("NE");
  states.push_back("LT");
  states.push_back("GT");
  states.push_back("LE");
  states.push_back("GE");
  states.push_back("PLUS");
  states.push_back("MINUS");
  states.push_back("STAR");
  states.push_back("SPLASH");
  states.push_back("PCT");
  states.push_back("COMMA");
  states.push_back("SEMI");
  //states.push_back("WHITESPACE");
  states.push_back("COMMENT");
  /*states.push_back("I");
  states.push_back("IN");
  states.push_back("E");
  states.push_back("EL");
  states.push_back("ELS");
  states.push_back("W");
  states.push_back("WH");
  states.push_back("WHI");
  states.push_back("WHIL");
  states.push_back("R");
  states.push_back("RE");
  states.push_back("RET");
  states.push_back("RETU");
  states.push_back("RETUR");*/


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
  transFunc.emplace(std::pair<std::string,std::string>("start","/"),"SPLASH");
  transFunc.emplace(std::pair<std::string,std::string>("SPLASH","/"),"COMMENT");
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
      if(key.second!= "NOT" && key.second!= "COMMENT"){
        finalStates.push_back(key.second);
      }
    }
  }


  /*transFunc.emplace(std::pair<std::string,std::string>(,"n"),"IN");
  transFunc.emplace(std::pair<std::string,std::string>("start","i"),"I");
  transFunc.emplace(std::pair<std::string,std::string>("I","n"),"IN");
  transFunc.emplace(std::pair<std::string,std::string>("IN","t"),"INT");
  transFunc.emplace(std::pair<std::string,std::string>("start","e"),"E");
  transFunc.emplace(std::pair<std::string,std::string>("E","l"),"EL");
  transFunc.emplace(std::pair<std::string,std::string>("EL","s"),"ELS");
  transFunc.emplace(std::pair<std::string,std::string>("ELS","e"),"ELSE");
  transFunc.emplace(std::pair<std::string,std::string>("start","w"),"W");
  transFunc.emplace(std::pair<std::string,std::string>("W","h"),"WH");
  transFunc.emplace(std::pair<std::string,std::string>("WH","i"),"WHI");
  transFunc.emplace(std::pair<std::string,std::string>("WHI","l"),"WHIL");
  transFunc.emplace(std::pair<std::string,std::string>("WHIL","e"),"WHILE");
  transFunc.emplace(std::pair<std::string,std::string>("start","r"),"R");
  transFunc.emplace(std::pair<std::string,std::string>("R","e"),"RE");
  transFunc.emplace(std::pair<std::string,std::string>("RE","t"),"RET");
  transFunc.emplace(std::pair<std::string,std::string>("RET","u"),"RETU");
  transFunc.emplace(std::pair<std::string,std::string>("RETU","r"),"RETUR");
  transFunc.emplace(std::pair<std::string,std::string>("RETUR","n"),"RETURN");*/

  //transFunc.emplace(std::pair<std::string,std::string>("start",std::string(1,char(32))),"WHITESPACE");
  //transFunc.emplace(std::pair<std::string,std::string>("start",std::string(1,char(9))),"WHITESPACE");
  //transFunc.emplace(std::pair<std::string,std::string>("start",std::string(1,char(10))),"WHITESPACE");


  
  /*//print alphabet
  std::cout << alphabet.size() <<std::endl;
  for(std::string letter: alphabet){
    std::cout << letter <<std::endl;
  }

  //print states
  std::cout << states.size() <<std::endl;
  for(std::string state: states){
    std::cout << state <<std::endl;
  }

  //print initial state
  std::cout << states[0] <<std::endl;

  //print final states
  std::cout << finalStates.size() <<std::endl;
  for(std::string state: finalStates){
    std::cout << state <<std::endl;
  }

  //print transisions
  std::cout << transFunc.size() <<std::endl;
  for(auto key: transFunc){
    std::cout << key.first.first << " " << key.first.second << " " << key.second<<std::endl;
  }*/




  /*while(std::cin >> input){
  }*/

  return 0;
}

  




