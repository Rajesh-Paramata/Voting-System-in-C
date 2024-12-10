#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int MAX_VOTERS;
int MAX_CAND;

struct Candidate {
    char name[50];
    int id;
    int voteCount;
};

struct Voter {
    char name[50];
    int voterID;
    char nationality[30];
    bool hasVoted;
};

void printLine() {
    printf("\n************************************************************\n");
}

void registerCandidate(struct Candidate candidates[], int *numCandidates) {
    printf("The Maximum number of Candidates that can register is %d\n", MAX_CAND);
    printLine();
    if (*numCandidates == MAX_CAND) {
        printf("\nSorry, the maximum limit for candidates has been reached.\n");
        return;
    } else {
        struct Candidate newCandidate;
        while (*numCandidates < MAX_CAND) {
            printf("Enter the name of the candidate: ");
            scanf("%49s", newCandidate.name);

            newid:
            printf("Enter the ID of the candidate: ");
            scanf("%d", &newCandidate.id);

            // Check ID already taken
            for (int i = 0; i < *numCandidates; i++) {
                if (candidates[i].id == newCandidate.id) {
                    printf("Sorry, the ID is already taken. Please choose a different ID.\n");
                    goto newid;
                }
            }

            newCandidate.voteCount = 0;

            candidates[*numCandidates] = newCandidate;
            (*numCandidates)++;

            printf("\nCandidate registered successfully!\n");
        }
    }
}

void displayCandidates(struct Candidate candidates[], int numCandidates) {
    if (numCandidates == 0) {
        printf("No candidates registered yet.\n");
        return;
    }
    printLine();
    printf("\nRegistered candidates:\n");
    printf("----------------------\n");
    for (int i = 0; i < numCandidates; i++) {
        printf("Candidate Name: %s\n", candidates[i].name);
        printf("Candidate ID: %d\n", candidates[i].id);
        printf("----------------------\n");
    }
    printLine();
}

void addCandidate(struct Candidate candidates[], int *numCandidates) {
    if (*numCandidates >= MAX_CAND) {
        printf("Sorry, the maximum number of candidates has already been reached.\n");
        return;
    }

    struct Candidate newCandidate;

    printf("Enter the name of the candidate: ");
    scanf("%49s", newCandidate.name);

    printf("Enter the ID of the candidate: ");
    scanf("%d", &newCandidate.id);

    newCandidate.voteCount = 0;

    candidates[*numCandidates] = newCandidate;
    (*numCandidates)++;

    printf("Candidate added successfully!\n");
    printf("Updated Candidates list:\n");
    displayCandidates(candidates, *numCandidates);
}

void changeCandidate(struct Candidate candidates[], int numCandidates) {
    int candidateID;

    printf("Enter the ID of the candidate you want to change: ");
    scanf("%d", &candidateID);

    for (int i = 0; i < numCandidates; i++) {
        if (candidates[i].id == candidateID) {
            printf("Enter the new name of the candidate: ");
            scanf("%49s", candidates[i].name);

            printf("Candidate information updated successfully!\n");
            printf("Updated Candidate list:\n");
            displayCandidates(candidates, numCandidates);
            return;
        }
    }

    printf("Candidate with ID %d not found.\n", candidateID);
}

void deleteCandidate(struct Candidate candidates[], int *numCandidates) {
    int candidateID;

    printf("Enter the ID of the candidate you want to delete: ");
    scanf("%d", &candidateID);

    for (int i = 0; i < *numCandidates; i++) {
        if (candidates[i].id == candidateID) {
            for (int j = i; j < (*numCandidates) - 1; j++) {
                candidates[j] = candidates[j + 1];
            }

            (*numCandidates)--;
            printf("Candidate deleted successfully!\n");
            printf("Updated Candidates list:\n");
            displayCandidates(candidates, *numCandidates);
            return;
        }
    }

    printf("Candidate with ID %d not found.\n", candidateID);
}

void administration(struct Candidate candidates[], int *numCandidates) {
    char adminChoice;

    do {
        printf("Administrator Menu:\n");
        printf("1. Add Candidate\n");
        printf("2. Change Candidate\n");
        printf("3. Delete Candidate\n");
        printf("4. Display Candidates List\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &adminChoice);
        printf("\n");
        switch (adminChoice) {
            case '1':
                addCandidate(candidates, numCandidates);
                break;
            case '2':
                changeCandidate(candidates, *numCandidates);
                break;
            case '3':
                deleteCandidate(candidates, numCandidates);
                break;
            case '4':
                displayCandidates(candidates, *numCandidates);
                break;
            case '5':
                printf("Exiting Administration...\n");
                printLine();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (adminChoice != '5');
}

int registerVoter(struct Voter voters[], int numVoters) {
    printf("The maximum number of voters that can register to vote is %d\n", MAX_VOTERS);
    printf("----------------------\n");
    printf("Please enter the required details to register..\n");
    while (numVoters < MAX_VOTERS) {
        printf("----------------------\n");
        printf("Enter voter name: ");
        scanf("%49s", voters[numVoters].name);

        printf("Enter voter nationality: ");
        char nationality[50];
        scanf("%49s", nationality);

        // Check nationality
        if (strcasecmp(nationality, "Indian") != 0) {
            printf("Only Indian citizens are eligible to register as voters.\n");
            continue;
        }

        printf("Enter voter age: ");
        int age;
        scanf("%d", &age);

        if (age < 18) {
            printf("Voters must be 18 years or older to register.\n");
            continue;
        }

        voters[numVoters].voterID = numVoters + 1;
        voters[numVoters].hasVoted = false;

        printf("Voter registered successfully. Voter ID: %d\n", voters[numVoters].voterID);
        printf("----------------------\n");

        numVoters++;
    }

    return numVoters;
}

void castVote(struct Candidate candidates[], int numCandidates, struct Voter voters[], int numVoters) {
    int voterID, candidateID, candidateIndex;
    int voterIndex = -1;

    while (voterIndex == -1) {
        printf("----------------------\n");
        printf("Enter your registered Voter ID: ");
        scanf("%d", &voterID);

        // Find the voter by ID
        for (int i = 0; i < numVoters; i++) {
            if (voters[i].voterID == voterID) {
                voterIndex = i;
                break;
            }
        }

        if (voterIndex == -1) {
            printf("Invalid Voter ID. Please try again.\n");
        }
    }

    if (voters[voterIndex].hasVoted) {
        printf("\nYou have already cast your vote. Multiple votes are not allowed.\n");
        return;
    }

    printf("----------------------\n");
    printf("Candidates:\n");
    for (int i = 0; i < numCandidates; i++) {
        printf("ID: %d %s\n", candidates[i].id, candidates[i].name);
    }

    candidateIndex = -1;

    do {
        printf("Enter the Candidate ID you want to vote for (or enter 0 to skip): ");
        scanf("%d", &candidateID);

        if (candidateID == 0) {
            printf("Vote skipped.\n");
            return;
        }

        for (int i = 0; i < numCandidates; i++) {
            if (candidates[i].id == candidateID) {
                candidateIndex = i;
                break;
            }
        }

        if (candidateIndex == -1) {
            printf("Invalid Candidate ID. Please try again.\n");
        }

    } while (candidateIndex == -1);

    candidates[candidateIndex].voteCount++;
    voters[voterIndex].hasVoted = true;
    printf("----------------------\n");
    printf("Your vote for %s has been recorded. Thank you for voting!\n", candidates[candidateIndex].name);
    printf("----------------------\n");
}

void displayVoteCount(struct Candidate candidates[], int numCandidates) {
    printf("----------------------\n");
    printf("Vote Count:\n");
    for (int i = 0; i < numCandidates; i++) {
        printf("----------------------\n");
        printf("%s: %d\n", candidates[i].name, candidates[i].voteCount);
    }
}

void VotingResult(struct Candidate candidates[], int numCandidates) {
    int maxVotes = 0;
    int winnerIndex = -1;
    int numWinners = 0;

    for (int i = 0; i < numCandidates; i++) {
        if (candidates[i].voteCount > maxVotes) {
            maxVotes = candidates[i].voteCount;
            winnerIndex = i;
            numWinners = 1;
        } else if (candidates[i].voteCount == maxVotes) {
            numWinners++;
        }
    }

    if (numWinners == 1) {
        printf("THE WINNER IS %s WITH %d VOTES!\n", candidates[winnerIndex].name, candidates[winnerIndex].voteCount);
        printLine();
    } else if (numWinners > 1) {
        printf("It's a tie! There are %d Candidates with %d votes each.\n", numWinners, maxVotes);
        printf("----------------------\n");
        for (int i = 0; i < numCandidates; i++) {
            if (candidates[i].voteCount == maxVotes) {
                printf("%s\n", candidates[i].name);
            }
        }
    } else {
        printf("----------------------\n");
        printf("No winner. The votes are tied.\n");
    }
}

int main() {
    int numCandidates = 0;
    int numVoters = 0;
    char userResponse;

    printf("\t\t\t\tWELCOME TO MINI VOTING SYSTEM\n");
    printLine();
    printf("Enter the maximum number of Candidates came for registration:");
    scanf("%d",&MAX_CAND);
    printf("Enter the maximum number of voters came for registration:");
    scanf("%d",&MAX_VOTERS);

    struct Candidate candidates[MAX_CAND];
    struct Voter voters[MAX_VOTERS];

    printf("\nWe are now in the Candidate Registration Phase\nPlease enter the required details below to Register\n");
    registerCandidate(candidates, &numCandidates);

    printf("Do you want to display candidates list? (Y/N):");
    scanf(" %c", &userResponse);

    if (userResponse == 'Y' || userResponse == 'y') {
        displayCandidates(candidates, numCandidates);
    }

    printf("Do you want to make any modifications to the candidates? (Y/N): ");
    scanf(" %c", &userResponse);

    if (userResponse == 'Y' || userResponse == 'y') {
        administration(candidates, &numCandidates);
    }

    printf("We're entering the Registration phase for voters\n");
    printf("----------------------\n");
    numVoters = registerVoter(voters, numVoters);
    printf("Total number of registered voters: %d\n", numVoters);

    do {
        printf("\nAre you ready to move on to casting votes? (Y/N): ");
        scanf(" %c", &userResponse);
        if (userResponse == 'Y' || userResponse == 'y') {
            castVote(candidates, numCandidates, voters, numVoters);
        } else {
            printf("Exiting voting session.\n");
        }
    } while (userResponse != 'N' || userResponse != 'n');

    displayVoteCount(candidates, numCandidates);

    printf("Do you want to see the final results? (Y/N): ");
    scanf(" %c", &userResponse);
    if (userResponse == 'Y' || userResponse == 'y') {
        VotingResult(candidates, numCandidates);
    }

    return 0;
}
