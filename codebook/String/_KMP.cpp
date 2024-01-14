#include <bits/stdc++.h>
using namespace std;
struct KMP {
    string sub;
    vector<int> failure;
    KMP(string &sub) {
        this->sub = sub;
        failure.resize(sub.size(), -1);
        buildFailFunction();
    }
    void buildFailFunction() {
        for(int i = 1; i < sub.size(); i++) {
            int now = failure[i - 1];
            while(now != -1 && sub[now + 1] != sub[i]) now = failure[now];
            if (sub[now + 1] == sub[i]) failure[i] = now + 1;
        }
    }
    vector<int> KMPmatching(string &s) {
        vector<int> match;
        for(int i = 0, now = -1; i < s.size(); i++) {
            // now is the compare sucessed length -1
            while (s[i] != sub[now + 1] && now != -1) now = failure[now];
            // f stores if comparison fail, move to where
            if (s[i] == sub[now + 1]) now++;
            if (now + 1 == sub.size()) {
                match.push_back(i - now);
                now = failure[now];
            }
        }
        return match;
    }
};
int main(){
    string s = "xxtxxtxtx";
    string sub = "tx";
    KMP kmp(sub);
    vector<int> ans = kmp.KMPmatching(s);
    for(auto &i : ans) cout << i << " ";
}