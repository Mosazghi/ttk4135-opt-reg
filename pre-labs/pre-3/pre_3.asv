% TTK4135 - Helicopter lab
% Hints/template for problem 2.
% Updated spring 2018, Andreas L. Flåten

%% Initialization and model definition
init05; % Change this to the init file corresponding to your helicopter
Ac = [ 0      1        0          0;
       0      0      -K_2        0;
       0      0        0          1;
       0      0   -K_1*K_pp  -K_1*K_pd ];

Bc = [0;
      0;
      0;
      K_1*K_pp];

% Discrete time system model. x = [lambda r p p_dot]'
delta_t	= 0.25; % sampling time
sysc = ss(Ac,Bc,[],[]);          % C,D can be [] or zeros
% Discretize with zero‑order hold
sysd = c2d(sysc,delta_t);  % or 'tustin', 'foh', etc.

% Get Ad and Bd
% A1= sysd.A;
% B1 = sysd.B;
A1= eye(4) + delta_t  * Ac; 
B1 = delta_t * Bc; 
% Number of states and inputs
mx = size(A1,2); % Number of states (number of columns in A)
mu = size(B1,2); % Number of inputs(number of columns in B)

% Initial values
x1_0 = pi;                               % Lambda
x2_0 = 0;                               % r
x3_0 = 0;                               % p
x4_0 = 0;                               % p_dot
x0 = [x1_0 x2_0 x3_0 x4_0]';           % Initial values

% Time horizon and initialization
N  = 100;                                  % Time horizon for states
M  = N;                                 % Time horizon for inputs
z  = zeros(N*mx+M*mu,1);                % Initialize z for the whole horizon
z0 = z;                                 % Initial value for optimization

% Bounds
ul 	    = -1/6*pi;                      % Lower bound on control
uu 	    = 1/6*pi;              % Upper bound on control

xl      = -Inf*ones(mx,1);              % Lower bound on states (no bound)
xu      = Inf*ones(mx,1);               % Upper bound on states (no bound)
xl(3)   = ul;                           % Lower bound on state x3
xu(3)   = uu;                           % Upper bound on state x3

% Generate constraints on measurements and inputs
[vlb,vub]       = gen_constraints(N, M, xl, xu, ul, uu); % hint: gen_constraints
vlb(N*mx+M*mu)  = 0;                    % We want the last input to be zero
vub(N*mx+M*mu)  = 0;                    % We want the last input to be zero

% Generate the matrix Q and the vector c (objecitve function weights in the QP problem) 
Q1 = zeros(mx,mx);
Q1(1,1) = 2;                            % Weight on state x1
Q1(2,2) = 0;                            % Weight on state x2
Q1(3,3) = 0;                            % Weight on state x3
Q1(4,4) = 0;                            % Weight on state x4


P1 = 1;                                % Weight on input
H = gen_q(Q1, P1, N, M);                                  % Generate Q, hint: gen_q
c = zeros(N*mx+M*mu, 1);                % Generate c, this is the linear constant term in the QP

%% Generate system matrixes for linear model
Aeq = gen_aeq   (A1, B1, N, mx, mu);             % Generate A, hint: gen_aeq
beq = zeros(N*mx,1);
beq(1:mx,1) = A1 * x0;          % Generate b

%% Solve QP problem with linear model
tic
[z,lambda] = quadprog(2*H, c, [], [], Aeq, beq, vlb, vub, z0); % hint: quadprog. Type 'doc quadprog' for more info 
t1=toc;

% Calculate objective value
phi1 = 0.0;
PhiOut = zeros(N*mx+M*mu,1);
for i=1:N*mx+M*mu
  phi1=phi1+H(i,i)*z(i)*z(i);
  PhiOut(i) = phi1;
end

%% Extract control inputs and states
u  = [z(N*mx+1:N*mx+M*mu);z(N*mx+M*mu)]; % Control input from solution

x1 = [x0(1);z(1:mx:N*mx)];              % State x1 from solution
x2 = [x0(2);z(2:mx:N*mx)];              % State x2 from solution
x3 = [x0(3);z(3:mx:N*mx)];              % State x3 from solution
x4 = [x0(4);z(4:mx:N*mx)];              % State x4 from solution

num_variables = 5/delta_t;
zero_padding = zeros(num_variables,1);
unit_padding  = ones(num_variables,1);

u   = [zero_padding; u; zero_padding];
x1  = [pi*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];

%% Plotting
t = 0:delta_t:delta_t*(length(u)-1);
figure(2)
subplot(511)
stairs(t,u),grid
ylabel('u')
subplot(512)
plot(t,x1,'m',t,x1,'mo'),grid
ylabel('lambda')
subplot(513)
plot(t,x2,'m',t,x2','mo'),grid
ylabel('r')
subplot(514)
plot(t,x3,'m',t,x3,'mo'),grid
ylabel('p')
subplot(515)
plot(t,x4,'m',t,x4','mo'),grid
xlabel('tid (s)'),ylabel('pdot')

u_star = timeseries(u, t);
%% From Lab 3 (feedback)
Q = diag([100 1 1 1 1 1]);
R = [1; 1];
K = dlqr(A1,B1, Q, R);
x_star = timeseries([x1, x2, x3, x4], t);


x0_sim = [pi, -deg2rad(30),0,0,0,0]';

%% 
Ac = [ 0      1        0          0     0 0;
       0      0      -K_2        0      0 0;
       0      0        0          1     0 0;
       0      0   -K_1*K_pp  -K_1*K_pd  0 0;
       0      0        0         0      1 0;
       0      0        0          0     -K_3*K_ep -K_3*K_ed;
       ];

Bc = [0 0 ;
      0 0 ; 
      0 0;
      K_1*K_pp 0 ;
      0 0 ;
      0 K_3*K_ep
      ];
A1= eye(6) + delta_t  * Ac; 
B1 = delta_t * Bc; 
% Number of states and inputs
mx = size(A1,2); % Number of states (number of columns in A)
mu = size(B1,2); % Number of inputs(number of columns in B)
N = 40;
M = N;
z  = zeros(N*mx+M*mu,1);                % Initialize z for the whole horizon
z0 = z;                                 % Initial value for optimization

% Bounds
ul 	    = -1/6*pi;                      % Lower bound on control
uu 	    = 1/6*pi;              % Upper bound on control

xl      = -Inf*ones(mx,1);              % Lower bound on states (no bound)
xu      = Inf*ones(mx,1);               % Upper bound on states (no bound)
xl(3)   = ul;                           % Lower bound on state x3
xu(3)   = uu;                           % Upper bound on state x3

% Generate constraints on measurements and inputs
[vlb,vub]       = gen_constraints(N, M, xl, xu, ul, uu); % hint: gen_constraints
vlb(N*mx+M*mu)  = 0;                    % We want the last input to be zero
vub(N*mx+M*mu)  = 0;                    % We want the last input to be zero


Q1 = zeros(6,6);
Q1(1,1) = 1;       % weight on lambda (state 1)
q1 = 1; 
q2 = 1; 
P1 = diag([q1, q2]);   % weight on inputs: [p_c, e_c]
H = gen_q(Q1, P1, N, M);

c = zeros(N*mx+M*mu, 1);                % Generate c, this is the linear constant term in the QP

Aeq = gen_aeq(A1, B1, N, mx, mu);             % Generate A, hint: gen_aeq
beq = zeros(N*mx,1);
x0 = [pi 0 0 0 0 0]';           % Initial values
beq(1:mx,1) = A1 * x0;          % Generate b

f = @(z) z' * H *z;

function [c, ceq] = nonlin_constraints(z, N, mx, beta, lambda_t, alpha)
       c = zeros(N, 1); 
       ceq = [];
       % z = [x1 x2 x3 x4 x5 x6, x1 x2 x3 x4 x5 x6...
       for k = 1:N 
            e_k  = z((k-1)*mx + 5);
            lambda_k = z((k-1)*mx + 1);
            c(k) = alpha * exp(-beta* (lambda_k  - lambda_t)^2) - e_k;
       end
end
beta = 20; 
alpha = 0.2; 
lambda_t = 2*pi/3; 
nonlcon = @(z) nonlin_constraints(z, N, mx, beta, lambda_t, alpha);

z = fmincon(f, z0, [], [], Aeq, beq, vlb, vub, nonlcon);

%% 
%% Extract control inputs and states
% Inputs: u in z is interleaved [p_c0, e_c0, p_c1, e_c1, ...]
u_all = z(N*mx+1 : N*mx+M*mu);          % all 80 input elements
p_c   = u_all(1:mu:end);                % p_c: every 2nd starting at 1 → 40 elements
e_c   = u_all(2:mu:end);                % e_c: every 2nd starting at 2 → 40 elements

% Add final value to make same length as states (N+1)
p_c = [p_c; p_c(end)];
e_c = [e_c; e_c(end)];

% States: extract each from z
x1 = [x0(1); z(1:mx:N*mx)];            % lambda  (41 elements)
x2 = [x0(2); z(2:mx:N*mx)];            % r
x3 = [x0(3); z(3:mx:N*mx)];            % p
x4 = [x0(4); z(4:mx:N*mx)];            % p_dot
x5 = [x0(5); z(5:mx:N*mx)];            % e
x6 = [x0(6); z(6:mx:N*mx)];            % e_dot

% Padding (5 seconds before and after)
num_variables = 5 / delta_t;            % = 20
zero_padding  = zeros(num_variables, 1);
unit_padding  = ones(num_variables, 1);

p_c = [zero_padding; p_c; zero_padding];
e_c = [zero_padding; e_c; zero_padding];
x1  = [pi*unit_padding; x1; zero_padding];
x2  = [zero_padding; x2; zero_padding];
x3  = [zero_padding; x3; zero_padding];
x4  = [zero_padding; x4; zero_padding];
x5  = [zero_padding; x5; zero_padding];
x6  = [zero_padding; x6; zero_padding];

% Time vector — use x1 as reference length
t = 0:delta_t:delta_t*(length(x1)-1);

%% Plotting
figure(3)
subplot(4,1,1)
plot(t, x1), grid, ylabel('\lambda [rad]'), title('10.4 - States and Inputs')

subplot(4,1,2)
plot(t, x3), grid, ylabel('p [rad]')

subplot(4,1,3)
plot(t, x5), grid, ylabel('e [rad]')

subplot(4,1,4)
stairs(t, p_c, 'b'), hold on
stairs(t, e_c, 'r'), grid
ylabel('u'), xlabel('Time [s]')
legend('p_c', 'e_c')

%% Pass to Simulink
u_star = timeseries([p_c, e_c], t');
x_star = timeseries([x1, x2, x3, x4, x5, x6], t');
