from django.shortcuts import render, redirect
from .forms import GreetingForm
from .models import Greeting

def index(request):
    if request.method == 'POST':
        form = GreetingForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('/')
    else:
        form = GreetingForm()
            
    #получаем последнее приветствие или None
    last_greeting = Greeting.objects.last()

    context = {
        'form': form,
        'last_greeting': last_greeting,
    }
    return render(request, 'greetings/index.html', context)   