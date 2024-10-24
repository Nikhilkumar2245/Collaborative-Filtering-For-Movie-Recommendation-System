#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_MOVIES 5
#define NUM_USERS 4

// Structure to represent a movie
typedef struct {
    int id;
    char title[50];
    char genre[20];
} Movie;

// Structure to represent user ratings
typedef struct {
    int userId;
    int ratings[NUM_MOVIES];  // Ratings for each movie
} User;

// Movie data (ID, Title, Genre)
Movie movies[NUM_MOVIES] = {
    {1, "Inception", "sci-fi"},
    {2, "The Dark Knight", "action"},
    {3, "Interstellar", "sci-fi"},
    {4, "Pulp Fiction", "drama"},
    {5, "The Matrix", "sci-fi"}
};

// User ratings for movies (0-5 scale)
User users[NUM_USERS] = {
    {1, {5, 4, 3, 5, 2}},
    {2, {2, 3, 5, 3, 4}},
    {3, {5, 4, 2, 5, 3}},
    {4, {3, 5, 4, 2, 5}}
};

// Function to calculate similarity between users based on movie ratings
int calculate_similarity(int user1Ratings[], int user2Ratings[]) {
    int similarity = 0;
    for (int i = 0; i < NUM_MOVIES; i++) {
        similarity += abs(user1Ratings[i] - user2Ratings[i]);
    }
    return similarity;
}

// Function to get recommendations based on similarity and genre
void get_recommendations(int selectedMovieId, char selectedGenre[], int selectedUserId) {
    int bestUserId = -1;
    int minSimilarity = 9999;

    // Find the user most similar to the selected user (collaborative filtering)
    for (int i = 0; i < NUM_USERS; i++) {
        if (users[i].userId != selectedUserId) {
            int similarity = calculate_similarity(users[selectedUserId - 1].ratings, users[i].ratings);
            if (similarity < minSimilarity) {
                minSimilarity = similarity;
                bestUserId = users[i].userId;
            }
        }
    }

    printf("\nRecommended Movies (Genre: %s):\n", selectedGenre);
    // Recommend movies liked by the most similar user and match the genre
    for (int i = 0; i < NUM_MOVIES; i++) {
        if (users[bestUserId - 1].ratings[i] >= 4 && strcmp(movies[i].genre, selectedGenre) == 0 && movies[i].id != selectedMovieId) {
            printf(" - %s\n", movies[i].title);
        }
    }
}

int main() {
    int selectedMovieId;
    char selectedGenre[20];

    // Ask the user for input
    printf("Select a movie by ID (1-5):\n");
    for (int i = 0; i < NUM_MOVIES; i++) {
        printf("%d. %s (%s)\n", movies[i].id, movies[i].title, movies[i].genre);
    }
    scanf("%d", &selectedMovieId);

    // Ask the user to select a genre
    printf("Select a genre (action, drama, sci-fi, horror):\n");
    scanf("%s", selectedGenre);

    // Call the function to get recommendations
    get_recommendations(selectedMovieId, selectedGenre, 1);  // Using user 1 as the base for simplicity

    return 0;
}
