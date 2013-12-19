// chbspasswd v0.1
// 
// A password generator inspired by XKCD 936: Password Strength and xkpasswd.net
// 
// Copyright (C) 2013-2014, Charles H. Leggett
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <GetOpt.h>

class CHBSPassword {

  public:

    CHBSPassword();
    
    std::string  getPassword();

    std::string  validSpecialCharacters;
    std::string  validSeparators;

    std::string  getWord();
    int          wordCount;
    int          wordMinimumLength;
    int          wordMaximumLength;

    std::string  wordCase;

    std::string  getSeparator();
    bool         separatorEnabled;
    std::string  separatorType;
    int          separatorCount;

    std::string  getPad ( std::string, std::string );
    int          setPad ( CHBSPassword& thisPassword, std::string padPosition, std::string padType, std::string padCount);
    int          padMinimumLength;
    int          padMaximumLength;

    static std::string  convertPadType ( std::string );
    static int          convertPadCount ( std::string );
    static bool         isValidPadType ( std::string );
    static bool         isValidPadCount ( int, int, int );

    std::string  getBefore();
    std::string  beforeType;
    int          beforeCount;

    std::string  getAfter();
    std::string  afterType;
    int          afterCount;

    std::string  getInside();
    std::string  insideType;
    int          insideCount;

    bool         eleetEnabled;

};

int showHelp();
int showVersion();
int showCHBS();

std::vector<std::string> tokenize ( std::string, char );

int main(int argc, char **argv) {

  bool DEBUG = true;

  int passwordCount;
  CHBSPassword thisPassword;

  int flag;
  std::vector<std::string> arguments;

  while ((flag = getopt(argc, argv, "a:b:c:e:hi:l:n:s:u:vw:x")) != EOF) {

    if ( flag == 'a' ) {

      // after - Add string of digits, special characters, or a combination to the end of the password.

      // Split command line arguments on comma delimiter.
      arguments = tokenize ( optarg, ',' );

      // Set pad variables
      thisPassword.setPad ( thisPassword, "after", arguments[0], arguments[1] );

    }

    else if ( flag == 'b' ) {

      // before - Add string of digits, special characters, or a combination to the beginning of the password.

      // Split command line arguments on comma delimiter.
      arguments = tokenize ( optarg, ',' );

      // Set pad variables
      thisPassword.setPad ( thisPassword, "before", arguments[0], arguments[1] );

    }

    else if ( flag == 'c' ) {

      // case - Modify the words to be upper, lower, initial, or mixed case 

      std::string caseType = optarg;

      thisPassword.wordCase = caseType;

    }
    
    else if ( flag == 'e' ) {

      // eleet - Make 1337sp3@k substitutions: a=@, e=3, i=!, l=1, o=0, and t=7.

      thisPassword.eleetEnabled = true;

    }

    else if ( flag == 'h' ) {

      // help - Display a message with usage information 

      showHelp();

      return 0;

    }

    else if ( flag == 'i' ) {

      // inside - Add string of digits, special characters, or a combination between the words inside the password.


      // Split command line arguments on comma delimiter.
      arguments = tokenize ( optarg, ',' );

      // Set pad variables
      thisPassword.setPad ( thisPassword, "inside", arguments[0], arguments[1] );

    }

    else if ( flag == 'l' ) {

      // length - Set minimum and maximum word length.

      arguments = tokenize ( optarg, ',' );

      thisPassword.wordMinimumLength = atoi(arguments[0].c_str());
      thisPassword.wordMinimumLength = atoi(arguments[1].c_str());

    }

    else if ( flag == 'n' ) {

      // number - Set number of passwords to create.

      std::string count = optarg;

      passwordCount = atoi(count.c_str());

    }

    else if ( flag == 's' ) {

      // seperator - Set the preferences and count of seperator characters between words and other strings.

      arguments = tokenize ( optarg, ',' );

      thisPassword.separatorType = arguments[0];
      thisPassword.separatorCount = atoi(arguments[1].c_str());

    }

// Planned implementation in v0.2
//    else if ( flag == 'u' ) {
//
//      // use - Specify a configuration file to use instead of the default .chbspasswdrc
//
//    }

    else if ( flag == 'v' ) {

      // version - Display a message with version information 

      showVersion();

      return 0;

    }

    else if ( flag == 'w' ) {

      // words - Set the number of words to use.

      std::string count = optarg;

      thisPassword.wordCount = atoi(count.c_str());

    }

    else if ( flag == 'x' ) {

      // xkcd - Override all other options and return a well known password that you have already memorized. ;-)

      showCHBS();

      return 0;

    }

  }

  if ( DEBUG ) {
    std::cout << "beforeType: " << thisPassword.beforeType << std::endl; // debug message
    std::cout << "beforeCount: " << thisPassword.beforeCount << std::endl; // debug message
    std::cout << "insideType: " << thisPassword.insideType << std::endl; // debug message
    std::cout << "insideCount: " << thisPassword.insideCount << std::endl; // debug message
    std::cout << "afterType: " << thisPassword.afterType << std::endl; // debug message
    std::cout << "afterCount: " << thisPassword.afterCount << std::endl; // debug message
  }

  thisPassword.getPassword();
}

CHBSPassword::CHBSPassword() {

  // Define valid character types
  validSpecialCharacters = "~!@#$%^&*?";
  validSeparators = "~,.-_=+:";

  // Set defaults for password to be similar to: 5.Cool.Mountain.Africa.$
  wordCount = 3;
  wordMinimumLength = 3;
  wordMaximumLength = 8;

  wordCase = "INITIAL";

  separatorEnabled = true;
  separatorType = "SAME";
  separatorCount = 1;

  padMinimumLength = 1;
  padMaximumLength = 10;

  beforeType = "DIGITS";
  beforeCount = 1;

  afterType = "SPECIAL";
  afterCount = 1;

  insideType = "NONE";
  insideCount = 0;

  eleetEnabled = false;

}

std::string CHBSPassword::getPassword(){

  // Build and return password based on the defaults in the configuration file and modifying switches.

}

std::string CHBSPassword::getBefore() {

  // Return string for ...
  // before - Add string of digits, special characters, or a combination to the beginning of the password.
  
}

std::string CHBSPassword::getAfter() {

  // Return string for ...
  // after - Add string of digits, special characters, or a combination to the end of the password.

}

std::string CHBSPassword::getInside() {

  // Return string for ...
  // inside - Add string of digits, special characters, or a combination between the words inside the password.

}

std::string CHBSPassword::getPad ( std::string padType, std::string count ){

  // Called by get{Before,After,Inside} to use variables to build and return string.
  
}

int CHBSPassword::setPad ( CHBSPassword& thisPassword, std::string padPosition, std::string padType, std::string padCount ) {

  // Convert padType for validation comparison.
  std::string type = CHBSPassword::convertPadType ( padType );

  // Convert padCount for validation comparison.
  int Count = CHBSPassword::convertPadCount ( padCount );

  // Validate padType is one of the accepted types
  //   and
  // Validate padCount is within minimum to maximum length range

  if ( CHBSPassword::isValidPadType ( type )
         &&
       CHBSPassword::isValidPadCount ( Count, thisPassword.padMinimumLength, thisPassword.padMaximumLength ) ) {

    // Assign correct class variables based on padPosition.
    if ( padPosition == "before" ) {

      thisPassword.beforeType = type;
      thisPassword.beforeCount = Count;

    }
    else if ( padPosition == "inside" ) {

      thisPassword.insideType = type;
      thisPassword.insideCount = Count;

    }
    else if ( padPosition == "after" ) {

      thisPassword.afterType = type;
      thisPassword.afterCount = Count;

    }
    else {

      return -1;

    }

  }

}

std::string CHBSPassword::convertPadType ( std::string padType ) {

  // Convert string padType to upper case string for later comparison in validation function.

  std::transform(padType.begin(), padType.end(), padType.begin(), ::toupper);

  return padType;

}

int CHBSPassword::convertPadCount ( std::string padCount ) {

  // Convert string padCount to int Count.

  int Count = atoi(padCount.c_str());

  return Count;

}

bool CHBSPassword::isValidPadType ( std::string padType ) {

  if ( padType == "D" || padType == "DIGITS") {
    // Using Pad of Digits
    
    return 1;
  }
  else if ( padType == "S" || padType == "SPECIAL") {
    // Using Pad of Special Characters
    
    return true;
  }
  else if ( padType == "M" || padType == "MIXED") {
    // Using Pad of Mixed Digits and Special Characters
    
    return true;
  }
  else {
    // invalid argument
    std::cout << "./chbspasswd: unexpected argument -- " << padType << std::endl;
    showHelp();

    return false;
  }

}

bool CHBSPassword::isValidPadCount ( int padCount, int padMinimumLength, int padMaximumLength ) {

  if ( padCount <= padMaximumLength ) {
    return true;
  }
  else {
    return false;
  }

}

int showHelp() {

  // help - Display a message with usage information 

  std::cout << std::endl;
  std::cout << "Usage: chbspasswd [ -w numberOfWords ]" << std::endl;
  std::cout << "                  [ -l minimumWordLength,maximumWordLength ]" << std::endl;
  std::cout << "                  [ -c {UPPER|LOWER|INITIAL|MIXED} ]" << std::endl;
  std::cout << "                  [ -s typeOfSeparator,count ]" << std::endl;
  std::cout << "                  [ -{a|b|c} {DIGITS|SPECIAL|MIXED},count ]" << std::endl;
  std::cout << "                  [ -n numberOfPasswordsToGenerate ]" << std::endl;
  std::cout << std::endl;
  std::cout << "For more detailed information: man chbspasswd" << std::endl;
  std::cout << std::endl;

  return 0;
  
}

int showVersion() {

  // version - Display a message with version information 

  std::cout << "chbspasswd v0.1" << std::endl;

  return 0;

}

int showCHBS() {

  // xkcd - Override all other options and return a well known password that you have already memorized. ;-)

  std::cout << "CorrectHorseBatteryStaple" << std::endl;

  return 0;

}

std::vector<std::string> tokenize(std::string delimiterSeparatedString, char delimiter) {

  // Accepts a delimiter separated string and the specified delimiter.
  
  std::istringstream iss(delimiterSeparatedString);

  // Tokenizes the string and puts the tokens into a vector
  
  std::string token;
  std::vector<std::string> tokens;
  
  while (std::getline(iss, token, delimiter)) {
    tokens.push_back(token);
  }

  // Returns the vector.

  return tokens;

};

