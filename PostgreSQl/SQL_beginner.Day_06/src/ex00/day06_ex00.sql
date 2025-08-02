DROP TABLE IF EXISTS person_discounts;

-- Create a new table 'TableName' with a primary key and columns

CREATE TABLE IF NOT EXISTS person_discounts (
    id BIGINT PRIMARY KEY,
    person_id BIGINT,
    pizzeria_id BIGINT,
    discount NUMERIC, 
    constraint fk_person_discounts_person_id foreign key (person_id) references person(id),
    constraint fk_person_discounts_pizzeria_id foreign key (pizzeria_id) references pizzeria(id)
);