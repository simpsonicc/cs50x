import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():

    stocks = db.execute("SELECT * FROM purchased WHERE user_id = ?", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash[0]["cash"] if cash else 0.0

    return render_template("index.html", stocks=stocks, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if (request.method == "POST"):
        user = request.form.get("username")
        row = db.execute("SELECT * FROM users WHERE username = ?", user)
        if ((len(row)) == 0):
            return apology("Incorrect username")
        symbol = request.form.get("symbol")
        no_shares = request.form.get("shares")
        purchase = lookup(symbol)

        if symbol is None:
            return apology("please enter symbol")
        total_price = float(purchase["price"]) * int(no_shares)
        result = db.execute("SELECT * FROM users WHERE username = ?", user)
        if (result[0]["cash"] < total_price):
            return apology("you don't have enough cash to purchase the stocks")
        else:
            new_price = float(result[0]["cash"]) - total_price
            db.execute("UPDATE users SET cash = ? WHERE username = ?", new_price, user)
            db.execute("INSERT INTO purchased(symbol, shares, price, user_id, type, timestamp) VALUES(?, ?, ?, ?, 'buy', datetime('now'))",
                       symbol, no_shares, total_price, session["user_id"])
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    transaction_history = db.execute("SELECT * FROM purchased WHERE user_id=?", session["user_id"])
    return render_template("history.html", history=transaction_history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if (request.method == "POST"):
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if (request.method == "POST"):
        stock_symbol = request.form.get("symbol")
        stock_details = lookup(stock_symbol)
        """Get stock quote."""
        if not stock_details:
            return apology("please enter correct stock symbol", 400)
        return render_template("quoted.html", result=stock_details)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if (request.method == "POST"):
        if (request.form.get("password")) != (request.form.get("confirmation")):
            return apology("passwords do not match")
        row = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if (len(row) != 0):
            return apology("username already exist")

        else:
            password_entered = request.form.get("password")
            username_entered = request.form.get("username")
            confirmation = request.form.get("confirmation")

            if not username_entered or not password_entered or not confirmation:
                return apology("all fields are required", 400)

            pass_hash = generate_password_hash(password_entered)
            cash_available = 10000.0
            db.execute("INSERT INTO users (username, hash, cash) VALUES(?, ?, ?)",
                       username_entered, pass_hash, cash_available)
            id = db.execute("SELECT id FROM users WHERE username = ? AND hash = ?",
                            username_entered, pass_hash)
            session["user_id"] = id[0]["id"]

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    stocks = db.execute("SELECT * from purchased WHERE user_id = ?", session["user_id"])
    if (request.method == "GET"):
        return render_template("sell.html")

    else:
        symbol = request.form.get("symbol").lower()
        shares = request.form.get("shares")
        row2 = lookup(symbol)
        if (row2 == None):
            return apology("incorrect stock symbol")
        if not (symbol == stocks[0]["symbol"]):
            return apology("you don't have this stock")
        share = stocks[0]["shares"]
        if (int(shares) > int(share)):
            return apology("you don't have enough shares to sell")
        share = int(share) - int(shares)
        price = row2["price"] * int(share)
        price = price + int(stocks[0]["price"])
        db.execute("UPDATE purchased SET shares = ?, price = ?, type = 'sell', timestamp = datetime('now') WHERE user_id = ? AND symbol = ?",
                   share, price, session["user_id"], symbol)
        db.execute("UPDATE users SET cash = ? WHERE id=?", price, session["user_id"])
    return redirect("/")

@app.route("/changepass", methods=["GET", "POST"])
@login_required
def changepass():
    if (request.method == "POST"):
        current_pass = request.form.get("current")
        new_pass = request.form.get("new")
        confirm_pass = request.form.get("confirm")
        old_hash = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])
        old_hash = old_hash[0]["hash"]
        if not check_password_hash(old_hash, current_pass):
            return apology("incorrect password")
        if (new_pass != confirm_pass):
            return apology("passwords don't match")

        new_hash = generate_password_hash(confirm_pass)
        db.execute("UPDATE users SET hash = ? WHERE id = ?", new_hash, session["user_id"])

        return redirect("/")
    else:
        return render_template("changepass.html")



