var app = angular.module("RE_App", []);


app.controller("RobotEventsController", function ($scope, $http) {
  
    $scope.GetTeams = function () {
        alert("API Call via Angular!!");
        $http.get('RobotEvents/GetTeams').then(function (response) {
            $scope.TeamList = response.data;
        });
    }
    //$scope.GetEvents = function () {
    //    alert("API Call via Angular!!");
    //    $http.get('RobotEvents/GetEvents').then(function (response) {
    //        $scope.EventList = response.data;
    //    });
    //}
    //$scope.GetPrograms = function () {
    //    alert("API Call via Angular!!");
    //    $http.get('RobotEvents/GetPrograms').then(function (response) {
    //        $scope.ProgramList = response.data;
    //    });
    //}
    
});
