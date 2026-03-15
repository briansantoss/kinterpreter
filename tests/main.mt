work GetName(): String {
        return "Aquiles Trindade"
}

work Main(): Int {
        // Here we have directly printing.
        String name = "Aquiles, Trindade"
        Print -> name, "\n"

        // Now lets try getting the name from the function.
        String name = GetName()
        Print -> name, "\n"
        return -> 0
}