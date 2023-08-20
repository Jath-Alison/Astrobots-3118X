var app = angular.module("RE_App", []);


app.controller("RobotEventsController", function ($scope, $http) {
  
    $scope.GetTeams = function () {
        alert("API Call via Angular!!");
        $http.get('RobotEvents/GetTeams').then(function (response) {
            $scope.TeamList = response.data;
        });
    }
});
