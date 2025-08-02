COMMENT ON TABLE person_discounts IS 'Personal discount system table that stores individual discount rates for customers in specific pizzerias. This table supports the business feature of personalized pricing and customer loyalty programs by tracking discount percentages based on order history.';

COMMENT ON COLUMN person_discounts.id IS 'Primary key - unique identifier for each discount record. Auto-generated sequential number.';

COMMENT ON COLUMN person_discounts.person_id IS 'Foreign key reference to person table. Identifies the customer who receives the personal discount.';

COMMENT ON COLUMN person_discounts.pizzeria_id IS 'Foreign key reference to pizzeria table. Identifies the restaurant where the discount is applicable.';

COMMENT ON COLUMN person_discounts.discount IS 'Discount percentage value (0-100). Represents the personal discount rate applied to orders. Calculated based on customer order history: 1 order = 10.5%, 2 orders = 22%, 3+ orders = 30%.';


SELECT obj_description('person_discounts'::regclass);


SELECT column_name,
       col_description('person_discounts'::regclass, ordinal_position) as comment
FROM information_schema.columns
WHERE table_name = 'person_discounts';