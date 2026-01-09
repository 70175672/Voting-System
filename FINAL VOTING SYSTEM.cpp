#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_CANDIDATES = 10;
const int MAX_VOTERS = 100;

class Candidate {
private:
    string name;
    int votes;
public:
    Candidate() { name = ""; votes = 0; }
    void setName(string n) { name = n; }
    string getName() { return name; }
    int getVotes() { return votes; }
    void addVote() { votes++; }
    void setVotes(int v) { votes = v; }
};


class VotingSystem {
private:
    Candidate candidates[MAX_CANDIDATES];
    string voterIDs[MAX_VOTERS];
    string voterChoices[MAX_VOTERS];
    int numCandidates;
    int numVoters;
    bool votingActive;

public:
    VotingSystem() { numCandidates = 0; numVoters = 0; votingActive = false; }

    void loadCandidates() {
        ifstream file("candidates.txt");
        if (!file) return;
        string name;
        int votes;
        while (file >> votes) {
            file.ignore();
            getline(file, name);
            candidates[numCandidates].setName(name);
            candidates[numCandidates].setVotes(votes);
            numCandidates++;
        }
        file.close();
    }

    void saveCandidates() {
        ofstream file("candidates.txt");
        for (int i = 0; i < numCandidates; i++)
            file << candidates[i].getVotes() << " " << candidates[i].getName() << endl;
        file.close();
    }

    void loadVoters() {
        ifstream file("voters.txt");
        if (!file) return;
        string voterID, candidateName;
        while (file >> voterID) {
            file.ignore();
            getline(file, candidateName);
            voterIDs[numVoters] = voterID;
            voterChoices[numVoters] = candidateName;
            numVoters++;
        }
        file.close();
    }

    void saveVoters() {
        ofstream file("voters.txt");
        for (int i = 0; i < numVoters; i++)
            file << voterIDs[i] << " " << voterChoices[i] << endl;
        file.close();
    }

    void addCandidate(string name) {
        if (votingActive) {
            cout << "Cannot add candidates while voting is active!\n";
            return;
        }
        if (numCandidates < MAX_CANDIDATES) {
            candidates[numCandidates].setName(name);
            numCandidates++;
            saveCandidates();
            cout << "Candidate added: " << name << endl;
        } else {
            cout << "Maximum candidates reached!\n";
        }
    }

    void removeCandidate(int choice) {
        if (votingActive) {
            cout << "Cannot remove candidates while voting is active!\n";
            return;
        }
        if (choice > 0 && choice <= numCandidates) {
            cout << "Candidate removed: " << candidates[choice-1].getName() << endl;
            for (int i = choice - 1; i < numCandidates - 1; i++)
                candidates[i] = candidates[i + 1];
            numCandidates--;
            saveCandidates();
        } else {
            cout << "Invalid candidate number!\n";
        }
    }

    void showCandidates(bool showVotes = false) {
        if (numCandidates == 0) {
            cout << "No candidates available!\n";
            return;
        }
        cout << "\nList of Candidates:\n";
        for (int i = 0; i < numCandidates; i++) {
            cout << i + 1 << ". " << candidates[i].getName();
            if (showVotes) cout << " (" << candidates[i].getVotes() << " votes)";
            cout << endl;
        }
    }

    void castVote(string voterID, int choice) {
        if (!votingActive) {
            cout << "Voting is not active.\n";
            return;
        }
        for (int i = 0; i < numVoters; i++) {
            if (voterIDs[i] == voterID) {
                cout << "You have already voted!\n";
                return;
            }
        }
        if (choice > 0 && choice <= numCandidates) {
            candidates[choice - 1].addVote();
            voterIDs[numVoters] = voterID;
            voterChoices[numVoters] = candidates[choice - 1].getName();
            numVoters++;
            saveCandidates();
            saveVoters();
            cout << "Vote casted for " << candidates[choice - 1].getName() << endl;
        } else {
            cout << "Invalid candidate choice!\n";
        }
    }

    void showResults(bool hideVotes = true) {
        if (numVoters == 0) {
            cout << "No votes cast yet.\n";
            return;
        }
        cout << "\nVoting Results:\n";
        for (int i = 0; i < numCandidates; i++) {
            double percent = (double)candidates[i].getVotes() / numVoters * 100;
            cout << candidates[i].getName() << " - ";
            if (hideVotes) {
                cout << "Votes hidden until voting ends\n";
            } else {
                cout << candidates[i].getVotes() << " votes (" << (int)percent << "%)\n";
            }
        }
        if (!hideVotes) cout << "Total votes: " << numVoters << endl;
    }

    void showWinner() {
        if (numVoters == 0) {
            cout << "No votes cast. No winner.\n";
            return;
        }
        int maxVotes = -1;
        string winners[MAX_CANDIDATES];
        int winnerCount = 0;
        for (int i = 0; i < numCandidates; i++) {
            if (candidates[i].getVotes() > maxVotes) {
                maxVotes = candidates[i].getVotes();
                winnerCount = 0;
                winners[winnerCount++] = candidates[i].getName();
            } else if (candidates[i].getVotes() == maxVotes) {
                winners[winnerCount++] = candidates[i].getName();
            }
        }
        cout << "\nWinner(s): ";
        for (int i = 0; i < winnerCount; i++) {
            cout << winners[i];
            if (i != winnerCount - 1) cout << ", ";
        }
        cout << endl;
    }

    void showVoterDetails() {
        if (numVoters == 0) {
            cout << "No votes cast yet.\n";
            return;
        }
        cout << "\nVoter Details:\n";
        for (int i = 0; i < numVoters; i++)
            cout << "Voter ID: " << voterIDs[i] << " -> Voted for: " << voterChoices[i] << endl;
    }

    void startVoting() { votingActive = true; cout << "Voting started.\n"; }
    void endVoting() { votingActive = false; cout << "Voting ended.\n"; }
    bool isVotingActive() { return votingActive; }
};

int main() {
    VotingSystem voting;
    voting.loadCandidates();
    voting.loadVoters();

    string adminPassword = "alishba25";
    string inputPassword;
    string voterID;
    int choice, option;

    cout << "===== Final Voting System with File Handling =====\n";

    do {
        cout << "\n1. Admin Login\n2. Cast Vote\n3. Show Results\n4. Show Winner\n5. Exit\n";
        cout << "Enter your option: ";
        cin >> option;

        switch (option) {
            case 1: {
                cout << "Enter admin password: ";
                cin >> inputPassword;
                if (inputPassword == adminPassword) {
                    int adminOption;
                    do {
                        cout << "\n--- Admin Menu ---\n";
                        cout << "1. Add Candidate\n2. Remove Candidate\n3. Show Candidates\n4. Start Voting\n5. End Voting\n6. Show Voter Details\n7. Back\n";
                        cout << "Enter option: ";
                        cin >> adminOption;
                        cin.ignore();
                        switch (adminOption) {
                            case 1: {
                                string name;
                                cout << "Enter candidate name: ";
                                getline(cin, name);
                                voting.addCandidate(name);
                                break;
                            }
                            case 2: {
                                voting.showCandidates();
                                cout << "Enter candidate number to remove: ";
                                int c; cin >> c;
                                voting.removeCandidate(c);
                                break;
                            }
                            case 3:
                                voting.showCandidates();
                                break;
                            case 4:
                                voting.startVoting();
                                break;
                            case 5:
                                voting.endVoting();
                                break;
                            case 6:
                                voting.showVoterDetails();
                                break;
                        }
                    } while (adminOption != 7);
                } else cout << "Incorrect password!\n";
                break;
            }
            case 2:
                cout << "Enter your Voter ID: ";
                cin >> voterID;
                voting.showCandidates();
                cout << "Enter candidate number to vote: ";
                cin >> choice;
                voting.castVote(voterID, choice);
                break;
            case 3:
                voting.showResults(voting.isVotingActive()); 
                break;
            case 4:
                voting.showResults(false); 
                voting.showWinner();
                break;
            case 5:
                cout << "Exiting system.\n";
                break;
            default:
                cout << "Invalid option!\n";
        }
    } while (option != 5);

    return 0;
}

