import os
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
# creates at instance a flask application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True
# This Flask configuration setting enables auto-reloading of templates during development when changes are made to the application

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")
# u can access ur database by SQL("sqlite://'db name.db'")


@app.after_request
# @app.after_request will alter response before sending it out to the user and return reponse
# get method is use to retrieve data while post method is used to send/submit data
# app.route defines url path
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response
# this makes sure everytime data is fetched its new
# u can use app.route instead but then u will have to add the response manually in each output


@app.route("/", methods=["GET", "POST"])
# app.route is a decorator that defines a route (URL path) for the web app.
def index():
    if request.method == "POST":
        # mandatory syntax to retrieve data based on name(like id in html)
        name = request.form.get('name')
        day = request.form.get('day')
        month = request.form.get('month')
        # TODO: Add the user's entry into the database
        # to add a row u use insert and to add a column u use alter
        db.execute(
            "INSERT INTO birthdays (name, day, month) VALUES (?, ?, ?);", name, day, month
        )
        return redirect("/")

    else:
        birthday = db.execute("SELECT name, month, day FROM birthdays")
        # birthday is a list

        # TODO: Display the entries in the database on index.html

        return render_template("index.html", birthdays=birthday)
    # jinga/jinga2(render_template) is a templating engine for python. It allows you to create dynamic HTML pages. This way u can use logic in ur html code too
    # flask.session stores data accross request
    # jsonify is a function that helps u create the python data into json format
    # Jinja2 Templating ({{ var }}, {% if %})
