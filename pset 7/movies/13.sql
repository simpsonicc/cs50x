SELECT people.name FROM people JOIN stars ON people.id = stars.person_id JOIN movies ON stars.movie_id = movies.id WHERE movies.id IN
(SELECT movies.id FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON stars.person_id = people.id
WHERE people.name = "Kevin Bacon") and people.name != "Kevin Bacon";

-- in operator allows u to compares a value to the list of values, unlike one that allows u to comapre to one value only
