#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank,string name, int ranks[])
{
    for(int i=0; i<candidate_count; i++)
    {
        string temp=candidates[i];
        if(strcmp(name, temp)==0)
        {
            //printf("rank %i is %s(%i)\n", rank, name, i);
            ranks[rank]= i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for(int i=0; i<candidate_count; i++)
    {
        for (int j=i+1; j<candidate_count; j++)
        {
            int tempi=ranks[i]; 
            int tempj=ranks[j];
            preferences[tempi][tempj] +=1;
            //printf("preference between %i and %i\n", tempi, tempj);
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int temp=0;
    for (int i=0; i<MAX; i++)
    {
        for (int j=0; j<MAX; j++)
        {
            if (preferences[i][j]>0)
            {
                pairs[temp].winner=i;
                pairs[temp].loser=j;
                temp +=1;
                pair_count++;
            }
        }
    }
    // //temporary print statement to check pairs array
    // for(int i=0; i<MAX * (MAX - 1) / 2; i++)
    // {
    //     printf("winner is %i loser is %i\n", pairs[i].winner, pairs[i].loser);
    // }
    // printf("pair count is %i\n", pair_count);
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for(int i=0; i<MAX * (MAX - 1) /2; i++)
    {
        for (int j=0; j<MAX * (MAX - 1) / 2; j++)
        {
            //if weight of pairs of j is < weight of pairs of j+1
            int j_winner_index=pairs[j].winner;
            int j_loser_index=pairs[j].loser;
            int jplus_winner_index=pairs[j+1].winner;
            int jplus_loser_index=pairs[j+1].loser;
            if(preferences[j_winner_index][j_loser_index] < preferences[jplus_winner_index][jplus_loser_index])
            {
                pair temp= pairs[j];
                pairs[j]=pairs[j+1];
                pairs[j+1]=temp;
            }
        }
    }
    // //temp loop to print sorted pairs
    // printf("sorted pairs are:\n");
    // for (int i=0; i<pair_count; i++)
    // {
    //     printf("winner is %i loser is %i\n", pairs[i].winner, pairs[i].loser);
    // }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int loserarray[candidate_count-1];
    for (int i=0; i<pair_count; i++)
    {
        if(i<candidate_count-1)
        {
            loserarray[i]=pairs[i].loser;
            locked[pairs[i].winner][pairs[i].loser]=true;
        }
        else
        {
            for(int j=0; j<candidate_count-1; j++)
            {
                if(loserarray[j]==pairs[i].loser)
                {
                    locked[pairs[i].winner][pairs[i].loser]=true;
                }
            }
        }

    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int temp=0;
    //collect all losers
    int losers[candidate_count-1];
    for(int i=0; i<pair_count; i++)
    {
        for(int j=0; j<pair_count; j++)
        {
            if(locked[i][j]==true)
            {
                losers[temp]=j;
                temp++;
            }
        }
    }
    //
    for(int i=0; i<candidate_count-1; i++)
    {
        for (int j=0; j<candidate_count-1; j++)
        {
            if (i==losers[j])
            {
                break;
            }

        }
        printf("%s\n", candidates[i]);
        return;
    }
}

