function [ x_out, y_out] = integration(signal)

  mean_signal = mean(s);
  y_out = cumsum(signal-mean_signal);
  x_out = cumsum(signal);
  
end


