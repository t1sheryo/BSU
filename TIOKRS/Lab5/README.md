# Lab 5, variant 21

Project for the assignment:
"Quadrilateral on the plane". A quadrilateral stores four vertices of type `Point2D`, can compute area and perimeter, determine its type (`SQUARE`, `RECTANGLE`, `RHOMBUS`, `ARBITRARY`), and uses exceptions for invalid input data.

What is included:
- `Point2D` and `Quadrilateral`
- `QuadrilateralAnalyzer` for processing an array of quadrilaterals
- JUnit 5 tests
- `DemoApp` with a console demonstration of constructors, methods, random array generation, grouping, and min/max search
- short TDD report source: `report/tdd-report.typ`

Main source files:
- `src/main/java/by/bsu/tiokrs/lab5/geometry/Point2D.java`
- `src/main/java/by/bsu/tiokrs/lab5/geometry/Quadrilateral.java`
- `src/main/java/by/bsu/tiokrs/lab5/geometry/QuadrilateralAnalyzer.java`
- `src/main/java/by/bsu/tiokrs/lab5/app/DemoApp.java`

Test files:
- `src/test/java/by/bsu/tiokrs/lab5/geometry/QuadrilateralTest.java`
- `src/test/java/by/bsu/tiokrs/lab5/geometry/QuadrilateralAnalyzerTest.java`

Run commands:
- `mvn test`
- `mvn -DskipTests package`
- `java -cp target/classes by.bsu.tiokrs.lab5.app.DemoApp 20 12345`

If Maven cannot access the global `.m2` directory in the current environment, use a local repository inside the project:
- `mvn "-Dmaven.repo.local=.m2/repository" test`
