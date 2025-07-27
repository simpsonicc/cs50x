SELECT movies.title, ratings.rating FROM movies JOIN ratings ON movies.id = ratings.movie_id WHERE movies.year = 2010 ORDER BY ratings.rating DESC, movies.title ASC;

-- you could add two order by with coma cos if the first order by doesn't comply it will take ssecond into account
