#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

bool in(char a, string b){
    for (char c : b) if (a==c) return true;
    return false;
}

string vowels = "eariotnslc";
int misvow = (1<<10);
vector< vector<string> > groups(misvow);

int let = 26;
ll letmask = (1<<let);
vector< vector<string> > dp(letmask, vector<string>(1, ":("));

int transmask(ll mask){
    int new_mask = 0;
    for (int i=0;i<10;i++){
        if (mask & (1<<(vowels[i]-'a'))){
            new_mask |= (1<<i);
        }
    }
    return new_mask;
}

vector<string> max_w(ll mask){
    if (dp[mask].size() && dp[mask][0] == ":("){
        dp[mask] = vector<string>();
        int opt_mask = transmask(mask);
        for (int i=0;i<groups[opt_mask].size();i++){
            string guess = groups[opt_mask][i];
            ll guess_mask = 0;
            for (int j=0;j<guess.size();j++){
                guess_mask |= (1<<(guess[j]-'a'));
            }
            if (mask & guess_mask) continue;
            vector<string> candidate = max_w(mask | guess_mask);
            candidate.push_back(guess);
            if (candidate.size() > dp[mask].size()){
                dp[mask] = candidate;
            }
        }
        cout<<mask<<": ";
        for (int i=0;i<dp[mask].size();i++){
            cout<<dp[mask][i]<<" ";
        }
        cout<<endl;
    }
    return dp[mask];
}

int main(){
    // read answers.txt
    ifstream answersFile("answers.txt");
    vector<string> answers;
    string line;
    while (getline(answersFile, line)) {
        answers.push_back(line);
    }
    answersFile.close();

    // read guesses.txt
    ifstream guessesFile("guesses.txt");
    vector<string> guesses;
    while (getline(guessesFile, line)) {
        guesses.push_back(line);
    }
    guessesFile.close();

    
    for (int i=0;i<misvow;i++){
        for (const string& guess : guesses) {
            bool ok = true;
            for (int j=0;j<10 && ok;j++){
                if (i & (1<<j)){
                    if (in(vowels[j], guess)) ok = false;
                }
            }
            if (ok) groups[i].push_back(guess);
        }
    }

    for (int i=0;i<answers.size();i++){
        ll answers_mask = 0;
        for (int j=0;j<5;j++) answers_mask |= (1<<(answers[i][j]-'a'));
        vector<string> max_words = max_w(answers_mask);
        ofstream outputFile("output.txt", ios::app);
        outputFile << "For answer: " << answers[i] << endl;
        for (const string& word : max_words) {
            outputFile << word << endl;
        }
        outputFile << endl;
        outputFile.close();
    }

    return 0;
}