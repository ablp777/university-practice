from django.db import models

class Greeting(models.Model):       #создает класс - таблицу Greeting
    name = models.CharField(max_length=100) #поле для хранения имени 100 символов