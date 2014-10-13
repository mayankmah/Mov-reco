/* Author: Mayank Maheshwari

This is the algorithm I'm working with.

Algorithm is do a Breadth-first search on the graph starting from the given node and store all the nodes in a vector.
   Sort the vector based on the rating by writing a comparator function that sorts based on the rating and return the number of movieIDs asked */


#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

using std::vector;
using std::list;

const int MAX_NUM_MOVIES = 100;


class Movie {
private:
    int movieId;
    float rating;
    vector<Movie*> similarMovies; // Similarity is bidirectional


struct list_comp
{
    bool operator () (const Movie* mov1, const Movie* mov2)
    {
            return (mov1->rating < mov2->rating);
    }

};

public:
    Movie(int movieId, float rating) {
        this->movieId = movieId;
        this->rating = rating;
    }

    int getId() {
        return movieId;
    }

    float getRating() {
        return rating;
    }

    void addSimilarMovie(Movie* movie) {
        similarMovies.push_back(movie);
        movie->similarMovies.push_back(this);
    }

    vector<Movie *>& getSimilarMovies() {
        return similarMovies;
    }


/*
     * Implement a function to return top rated movies in the network of movies
     * reachable from the current movie
     * eg:            A(Rating 1.2)
     *               /   \
     *            B(2.4)  C(3.6)
     *              \     /
     *               D(4.8)
     * In the above example edges represent similarity and the number is rating.
     * getMovieRecommendations(A,2) should return C and D (sorting order doesn't matter so it can also return D and C)
     * getMovieRecommendations(A,4) should return A, B, C, D (it can also return these in any order eg: B,C,D,A)
     * getMovieRecommendations(A,1) should return D. Note distance from A to D doesn't matter,
     *                             return the highest rated.
     *
     *     @param movie
     *     @param numTopRatedSimilarMovies
     *                      number of movies we want to return
     *     @return List of top rated similar movies
     */

        static void getMovieRecommendations(Movie* movie, int numTopRatedSimilarMovies, vector<Movie *> &recommendedMovies) {
       bool visited[MAX_NUM_MOVIES];
       for(int i = 0; i < MAX_NUM_MOVIES; i++)
        visited[i] = false;

    list<Movie*> mqueue;
    list<Movie*> sortmqueue;
    int j = 0;

    visited[movie->getId()] = true;
    mqueue.push_back(movie);

    list<Movie*>::iterator i;

    cout<<"Similar movies:\n";
    while(!mqueue.empty())
    {
        Movie* mov = mqueue.front();
        cout << mov->getId() << " ";
        mqueue.pop_front();
        sortmqueue.push_back(mov);

        vector<Movie*> mvec = mov->getSimilarMovies();
        for(int i = 0; i < mvec.size(); ++i)
        {
            if(!visited[mvec[i]->getId()])
            {
                visited[mvec[i]->getId()] = true;
                mqueue.push_back(mvec[i]);
            }
        }
    }

    //cout<<"Size:"<<sortmqueue.size();

    sortmqueue.sort(list_comp());

    //cout<<"Size:"<<sortmqueue.size();

    cout<<"\nSorted Movies:\n";
    for(i = sortmqueue.begin(); i != sortmqueue.end(); i++)
    cout<<(*i)->getId()<<" ";
    cout<<"\n";

    for(list<Movie*>::reverse_iterator i = sortmqueue.rbegin(); (j < numTopRatedSimilarMovies) && (i != sortmqueue.rend());++i)
    {
      recommendedMovies.push_back(*i);
      j++;
    }

    return;
    }

};


int main()
{
  Movie *m1 = new Movie(1, 1.2);
  Movie *m2 = new Movie(2, 2.4);
  Movie *m3 = new Movie(3, 3.6);
  Movie *m4 = new Movie(4, 4.8);
  Movie *m5 = new Movie(5, 0.5);
  Movie *m6 = new Movie(6, 1.1);
  Movie *m7 = new Movie(7, 6.2);
  Movie *m8 = new Movie(8, 6.1);


  m1->addSimilarMovie(m2);
  m1->addSimilarMovie(m3);
  m2->addSimilarMovie(m4);
  m3->addSimilarMovie(m4);
  m2->addSimilarMovie(m5);
  m6->addSimilarMovie(m7);
  m6->addSimilarMovie(m8);

  vector<Movie*> recommendedMovies;

  int v = 3;
  Movie::getMovieRecommendations(m2, v, recommendedMovies);
  cout<<"Recommended movies:\n";
  for(int i = 0; i < recommendedMovies.size(); i++)
  {
   cout<<recommendedMovies[i]->getId()<<" ";
  }

}
