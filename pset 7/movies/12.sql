SELECT movies.title FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id WHERE people.name = "Bradley Cooper"
INTERSECT
SELECT movies.title FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id WHERE people.name = "Jennifer Lawrence";
-- intersect allows u to excute same query but for two differnt items, name, texts, etc
