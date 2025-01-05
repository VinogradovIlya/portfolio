.items[]
| [
    .id,
    .created_at,
    .name,
    .has_test,
    (if .alternate_url then .alternate_url else "нет ссылки" end)
]
| @csv