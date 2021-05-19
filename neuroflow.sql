#query 1
SELECT MONTH(U.created_at) AS `month` ,
       YEAR(U.created_at) AS `year` , 
       (COUNT(*) / (SELECT Count(*) FROM users U
                    INNER JOIN excercises E
                    ON U.user_id = E.user_id 
                    WHERE MONTH(U.created_at) = MONTH(E.exercise_completion_date) 
                    AND YEAR(U.created_at) = YEAR(E.exercise_completion_date) )*100) AS `percentage completed`
  FROM users U
  INNER JOIN excercises E
    ON U.user_id = E.user_id
  WHERE MONTH(U.created_at) = MONTH(E.exercise_completion_date) AND YEAR(U.created_at) = YEAR(E.exercise_completion_date) 
  GROUP BY MONTH(U.created_at), Year(U.created_at)

#query 2
SELECT
   times,
   COUNT(1)
FROM( SELECT 
          E.user_id,
          COUNT(*) AS times
       FROM excercises E
       GROUP BY E.user_id) 
GROUP BY times

#query 3
SELECT P.organization_name as organization
       AVG(H.score) as average_scores
       INNER JOIN Phq9 as H 
       ON P.provider_id = H.provider_id
       GROUP BY P.organization_id
ORDER BY average_scores DESC
LIMIT 5  