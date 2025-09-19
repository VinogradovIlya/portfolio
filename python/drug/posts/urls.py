from django.urls import path
from . import views

app_name = 'posts'

urlpatterns = [
    # GET/POST /api/posts/
    path('', views.posts_list, name='posts_list'),
    # GET/PUT/DELETE /api/posts/{id}/
    path('<int:post_id>/', views.post_detail, name='post_detail'),

    # POST /api/posts/{id}/like/
    path('<int:post_id>/like/', views.post_like, name='post_like'),
    path('<int:post_id>/dislike/', views.post_dislike,
         name='post_dislike'),  # POST /api/posts/{id}/dislike/

    path('<int:post_id>/comments/', views.post_comments,
         name='post_comments'),  # GET/POST /api/posts/{id}/comments/

    path('comments/<int:comment_id>/replies/', views.comment_replies,
         name='comment_replies'),  # GET /api/posts/comments/{id}/replies/

    path('user/<int:user_id>/', views.user_posts,
         name='user_posts'),  # GET /api/posts/user/{id}/
]
