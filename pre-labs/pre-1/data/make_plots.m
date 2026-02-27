files = {'simout_P1.mat', 'simout_P02.mat', 'simout_P12.mat'};
labels = {'Travel [deg]', 'Travel rate [deg/s]', 'Pitch [deg]', ...
          'Pitch rate [deg/s]', 'Elevation [deg]', 'Elevation rate [deg/s]'};

for f = 1:length(files)
    data = load(files{f});
    fn = fieldnames(data);
    simout = data.(fn{1});  % auto-grab variable name
    
    t   = simout(1, :);     % Row 1: time
    sig = simout(2:7, :);   % Rows 2-7: signals

    figure('Position', [100 100 900 800]);
    for i = 1:6
        subplot(6, 1, i)
        plot(t, sig(i,:), 'b', 'LineWidth', 1.2)
        ylabel(labels{i})
        grid on
        if i == 1
            title(strrep(files{f}, '.mat', ''), 'Interpreter', 'none')
        end
        if i == 6
            xlabel('Time [s]')
        end
    end

    % Save as PNG
    saveas(gcf, strrep(files{f}, '.mat', '.png'))
    fprintf('Saved: %s\n', strrep(files{f}, '.mat', '.png'));
end
