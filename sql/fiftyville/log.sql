-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Find crime scene description
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';

-- Parking lot
SELECT license_plate, activity,hour, minute FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

-- ATM transaction
SELECT account_number, transaction_type FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street';


