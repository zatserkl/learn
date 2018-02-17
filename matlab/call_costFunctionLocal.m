%% define a few local functions in one file

%% NB: the only function with the same name as the file
%% will be visible to the outside world

%% function with the same name as this file: visible to the outer world
function call_costFunctionLocal()

initialTheta = zeros(2, 1);
printf('initialTheta: %f %f\n', initialTheta);

[jVal, gradient] = costFunctionLocal(initialTheta);
printf('initial: jVal = %f, gradient = [%f, %f]\n', jVal, gradient);

% optimize: fit the theta with fminunc (function minimization, unconstrained)

printf('\nCall fminunc: function minimization, unconstrained\n');

options = optimset('GradObj', 'on', 'MaxIter', 100);
[optTheta, costVal, exitFlag] = fminunc(@costFunctionLocal, initialTheta, options);

printf('optTheta: %.2f %.2f costVal = %.2f exitFlag = %d\n', optTheta, costVal, exitFlag);

% NB: to get description of the exitFlag (1 here) use:
% help fminunc 

end;

%% local function, invisible to the outer world
function [jVal, gradient] = costFunctionLocal(theta)

% returns value and partial derivatives of the test cost function
% (theta(1) - 5)^2 + (theta(2) - 5)^2

%% NB: this function has just one argument.
%% To call with additional arguments the function can be wrapped like in ex2.m:
%%
%% [theta, cost] = fminuc( @(t)(costFunction(t, X, y)), initial_theta, options);

%
% cost function is a function of the parameters theta only
% to compute the cost function you compare a prediction based on the parameters
% with the actual value. You sum up on all the training examples
%
% The actual cost function accepts as parameters X, y, theta. See computeCost.m
%
jVal = (theta(1) - 5)^2 + (theta(2) - 5)^2;

gradient = zeros(2, 1);
gradient(1) = 2*(theta(1) - 5);
gradient(2) = 2*(theta(2) - 5);

end;
