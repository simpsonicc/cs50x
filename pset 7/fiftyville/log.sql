-- Keep a log of any SQL queries you execute as you solve the mystery.

 Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted
  today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
| Littering took place at 16:36. No known witnesses.

SELECT activity, license_plate FROM bakery_security_logs WHERE year = 2024 and month = 7 and day = 28 and hour = 10 and minute = 15;

   | Jose    | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for
   my assistance in the case of the Irene Adler papers.”                                                                                                                               |
| Eugene  | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”                                                                                                                                                                                      |
| Barbara | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He
looked from one to the other of us, as if uncertain which to address.                                                                                                                   |
| Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security
footage from the bakery parking lot, you might want to look for cars that left
 the parking lot in that time frame.                                                          |
| Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by
the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that
 they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the
 flight ticket. |
| Lily    | Our neighboring courthouse has a very annoying rooster that crows loudly at 6am every day. My sons Robert and Patrick took the rooster to a city
far, far away, so it may never bother us again. My sons have successfully arrived in Paris.

SELECT account_number, amount FROM atm_transactions WHERE year = 2024 and month = 7 and day = 28 and atm_location = "Leggett Street" and transaction_type =
"withdraw";

| account_number | amount |
+----------------+--------+
| 28500762       | 48     |
| 28296815       | 20     |
| 76054385       | 60     |
| 49610011       | 50     |
| 16153065       | 80     |
| 25506511       | 20     |
| 81061156       | 30     |
| 26013199       | 35     |

SELECT caller, receIver FROM phone_calls WHERE year = 2024 and month = 7 and day = 28 and duration < 60;

+----------------+----------------+
|     caller     |    receiver    |
+----------------+----------------+
| (130) 555-0289 | (996) 555-8899 |
| (499) 555-9472 | (892) 555-8872 |
| (367) 555-5533 | (375) 555-8161 |
| (499) 555-9472 | (717) 555-1342 |
| (286) 555-6063 | (676) 555-6554 |
| (770) 555-1861 | (725) 555-3243 |
| (031) 555-6622 | (910) 555-3251 |
| (826) 555-1652 | (066) 555-9701 |
| (338) 555-6650 | (704) 555-2131 |
+----------------+----------------+


SELECT origin_airport_id, destination_airport_id, hour, minute FROM flights WHERE year = 2024 and month = 7 and day = 29;

| origin_airport_id | destination_airport_id | hour | minute |
+-------------------+------------------------+------+--------+
| 8                 | 6                      | 16   | 0      |
| 8                 | 11                     | 12   | 15     |
| 8                 | 4                      | 8    | 20     |
| 8                 | 1                      | 9    | 30     |
| 8                 | 9                      | 15   | 20     |

SELECT full_name, abbreviation FROM airports WHERE city = "Fiftyville";

|          full_name          | abbreviation |
+-----------------------------+--------------+
| Fiftyville Regional Airport | CSF          |

SELECT bank_accounts.person_id FROM bank_accounts WHERE account_number = 28500762 or account_number = 28296815 or account_number = 76054385 or account_number = 49610011
or account_number = 16153065 or account_number = 25506511 or account_number = 81061156 or account_number = 26013199;
SELECT people.name, people.phone_number, people.passport_number, bank_accounts.person_id

 person_id |
+-----------+
| 686048    |
| 514354    |
| 458378    |
| 395717    |
| 396669    |
| 467400    |
| 449774    |
| 438727    |


SELECT name, passport_number
FROM people
WHERE
  (
    id = 686048 OR id = 514354 OR id = 458378 OR id = 395717 OR
    id = 396669 OR id = 467400 OR id = 449774 OR id = 438727
  )
  AND
  (
    phone_number = "(130) 555-0289" OR phone_number = "(996) 555-8899" OR
    phone_number = "(499) 555-9472" OR phone_number = "(892) 555-8872" OR
    phone_number = "(367) 555-5533" OR phone_number = "(375) 555-8161" OR
    phone_number = "(717) 555-1342" OR phone_number = "(286) 555-6063" OR
    phone_number = "(676) 555-6554" OR phone_number = "(770) 555-1861" OR
    phone_number = "(725) 555-3243" OR phone_number = "(031) 555-6622" OR
    phone_number = "(910) 555-3251" OR phone_number = "(826) 555-1652" OR
    phone_number = "(066) 555-9701" OR phone_number = "(338) 555-6650" OR
    phone_number = "(704) 555-2131"
  );

  name   | passport_number |
+---------+-----------------+
| Kenny   | 9878712108      |
| Benista | 9586786673      |
| Taylor  | 1988161715      |
| Diana   | 3592750733      |
| Bruce   | 5773159633      |
+---------+-----------------+

SELECT flight_id, seat FROM passengers WHERE passport_number = " 9878712108 " OR passport_number = "9586786673" OR passport_number = "1988161715" OR passport_number =
"3592750733" OR passport_number = "5773159633";

| flight_id | seat |
+-----------+------+
| 5         | 7A   |
| 18        | 4C   |
| 24        | 2C   |
| 36        | 4A   |
| 36        | 6D   |
| 36        | 7A   |
| 42        | 9B   |
| 54        | 6C   |
+-----------+------+


SELECT destination_airport_id FROM flights WHERE (id = 5 OR id = 18 OR id = 24 OR id = 36 OR id = 42 OR id = 54) AND year = 2024 AND month = 7 AND day = 29;
SELECT full_name, city FROM airports WHERE id = 6 OR id = 4;

|          full_name          |     city      |
+-----------------------------+---------------+
| LaGuardia Airport           | New York City |
| Logan International Airport | Boston        |
+-----------------------------+---------------+
