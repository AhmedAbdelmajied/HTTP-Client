#include "HTTP_client.h"
#include "HTTP_Utils.h"
#include <vector>

using namespace std;

void parseInput(string input, vector<string> *result) {
  string temp;
  for(int i = 0; i < input.size(); i++) {
    if (input[i] == ' ' || input[i] == '\t') {
      result->push_back(temp);
      temp = "";
    } else {
      temp += input[i];
    }
  }
  if (temp != "")
    result->push_back(temp);
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
      cout << "Missing arguments!" << endl;
      exit(EXIT_FAILURE);
  }

  HTTP_client httpClient(atoi(argv[2]), argv[1]);
  httpClient.start();

  vector<string> result;
  string input;
  cout << "Enter your request:" << endl;
  getline(std::cin, input);
  do {
    parseInput(input, &result);
    cout << result.size() << endl;
    if (result.size() < 3) {
        cout << "ERROR: Invalid input!" << endl;
        httpClient.close_connection();
        exit(EXIT_FAILURE);
    }
    httpClient.execute(result[0], result[1], result[2]);
    getline(std::cin, input);
  } while(input != "exit");

  httpClient.close_connection();
  return 0;
}
