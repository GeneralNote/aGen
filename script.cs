$a = 0;

struct Animal:
    $type = "Dog";
    $name = "Jeff";
    $health = 100;

    def status():
        print("type = ", $type, "; name = ", $name, "; hp =", $health, ";\n");
    end
end

def fib($arg0):
    if ($arg0 == 0):
        return 0;
    end

    if ($arg0 == 1):
        return 1;
    end

    return fib($arg0 - 1) + fib($arg0 - 2);
end

def main():
    $loc0 = Animal();
    $loc0.status();

    return fib($a);
end