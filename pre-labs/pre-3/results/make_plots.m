files = {'data_Q_1_R_5.mat', 'data_Q_2_R_1.mat', 'data_Q_5_R_05.mat', ...
         'data_Q_10_R_05.mat', 'data_Q_12_R_1.mat', 'data_Q_100_R_1.mat'};
labels = {'Travel [deg]', 'Travel rate [deg/s]', 'Pitch [deg]', 'Pitch rate [deg/s]'};

for f = 1:length(files)
    data    = load(files{f});
    fn      = fieldnames(data);
    simout  = data.(fn{1});

    t    = simout(1, :);         % Row 1: time
    sig  = simout(2:5, :);       % Rows 2-5: first 4 states only

    % Trim to t <= 30s
    mask = t <= 30;
    t   = t(mask);
    sig = sig(:, mask);

    figure('Position', [100 100 700 750]);
    for i = 1:4
        subplot(4, 1, i)
        plot(t, sig(i,:), 'LineWidth', 1.2), grid on
        ylabel(labels{i})
        xlim([0 30])
        if i == 1
            title(strrep(files{f}, '.mat', ''), 'Interpreter', 'none')
        end
        if i == 4
            xlabel('Time [s]')
        end
    end

    saveas(gcf, strrep(files{f}, '.mat', '.png'))
end
