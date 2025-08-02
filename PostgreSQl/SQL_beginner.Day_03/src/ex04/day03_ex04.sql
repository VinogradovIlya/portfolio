with woman_order as
       (select p.name,
               p.gender,
               po.*,
               m.*,
               piz.name as pizzeria_name
        from person_order po
        join person p ON p.id = po.person_id
        join menu m ON m.id = po.menu_id
        join pizzeria piz ON piz.id = m.pizzeria_id
        where p.gender = 'female'),
     man_order as
       (select p.name,
               p.gender,
               po.*,
               m.*,
               piz.name as pizzeria_name
        from person_order po
        join person p ON p.id = po.person_id
        join menu m ON m.id = po.menu_id
        join pizzeria piz ON piz.id = m.pizzeria_id
        where p.gender = 'male')
       (select pizzeria_name
        from woman_order
        except select pizzeria_name
        from man_order)
UNION
       (select pizzeria_name
        from man_order
        except select pizzeria_name
        from woman_order)
order by pizzeria_name ;