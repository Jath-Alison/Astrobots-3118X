var app = angular.module("KC_App", ['angularUtils.directives.dirPagination']);

app.controller("MyController", function ($scope) { //function is called model
    $scope.MyVal = "Welcome to KSADS-COMP LLC";
    $scope.MyFnc = function () {
        alert("This is called via angular function!!!");
    }
    $scope.MyFncwithP = function (d) {
        alert("The value that is passed is: " + d);
    }
});

app.controller("InterviewModulesController", function ($scope, $http) {
    $scope.Headertext = "The following are the available modules for Interview.";
    $scope.GetModules = function () {
        alert("Hi");
        $http.get('KCModules/Index').then(function (response) {
            $scope.ModList = response.data;
        });
    }
});

app.controller("QuestionsController", function ($scope, $http) {

    $scope.Sort = function (col) {
        $scope.Key = col;
        $scope.AscorDesc = !$scope.AscorDesc;
    };
    $scope.GetQuestions = function () {
        alert("Hi");
        $http.get('KCQuestions/GetQuestions').then(function (response) {
            $scope.QuestionList = response.data;
        });
    };
    $scope.GetQuestionsMyMod = function (ModID) {
        alert("Hi");
        $http.get('KCQuestions/GetQuestionsByModID/' + ModID).then(function (response) {
            $scope.QuestionList = response.data;
        });
    };
});

app.controller("UDServicesController", function ($scope, MyCalciService) {
    $scope.Add = function (a, b) {
        $scope.res = MyCalciService.Add(a, b);
    };
    $scope.Subract = function (a, b) {
        $scope.res = MyCalciService.Subract(a, b);
    };
    $scope.Multiply = function (a, b) {
        $scope.res = MyCalciService.Multiply(a, b);
    };
    $scope.Divide = function (a, b) {
        $scope.res = MyCalciService.Divide(a, b);
    };

})




/*USER DEFINED SERVICES*/
/*SERVICE METHOD*/
//app.service("MyCalciService", function () {
//    this.Add = function (a, b) {
//        return parseInt(a) + parseInt(b);
//    };
//    this.Subract = function (a, b) {
//        return parseInt(a) - parseInt(b);
//    };
//    this.Multiply = function (a, b) {
//        return parseInt(a) * parseInt(b);
//    };
//    this.Divide = function (a, b) {
//        return parseInt(a) / parseInt(b);
//    };
//});

/*FACTORY METHOD Note: generally we prefer the factory Method..*/
app.factory("MyCalciService", function () {
    fact = {};
    fact.Add = function (a, b) {
        return parseInt(a) + parseInt(b);
    };
    fact.Subract = function (a, b) {
        return parseInt(a) - parseInt(b);
    };
    fact.Multiply = function (a, b) {
        return parseInt(a) * parseInt(b);
    };
    fact.Divide = function (a, b) {
        return parseInt(a) / parseInt(b);
    };
    return fact;
});
