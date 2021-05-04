SELECT MAX(Salary) AS SecondHighestSalary FROM Employee WHERE Salary not in (SELECT MAX(Salary) from Employee)

-- SELECT DISTINCT Salary FROM Employee ORDER BY DESC LIMIT 1 OFFSET 1 AS SecondHighestSalary

SELECT
(SELECT DISTINCT Salary FROM Employee ORDER BY Salary DESC LIMIT 1 OFFSET 1)
AS SecondHighestSalary