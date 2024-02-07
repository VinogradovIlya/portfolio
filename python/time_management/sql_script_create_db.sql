CREATE DATABASE IF NOT EXISTS my_lessons;
USE my_lessons;

CREATE TABLE IF NOT EXISTS my_lessons.lesson (
	id SERIAL,
	type_lesson CHAR(1),
    surname VARCHAR(45),
    time CHAR(5),
    date DATE
);

CREATE TABLE IF NOT EXISTS my_lessons.type_lesson (
	id SERIAL,
    type_num CHAR(1),
    type_lesson VARCHAR(6)
);

INSERT INTO my_lessons.type_lesson (type_num, type_lesson)
VALUES 
(1, 'группа'),
(2, 'индив');

SELECT * FROM my_lessons.lesson;

-- DROP DATABASE my_lessons;