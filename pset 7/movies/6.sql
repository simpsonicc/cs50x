SELECT avg(ratings.rating) FROM ratings JOIN movies ON ratings.movie_id = movies.id WHERE movies.year = 2012;

