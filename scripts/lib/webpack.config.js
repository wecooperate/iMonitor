module.exports = {
  //mode: "development",
  mode: "production",
  
  entry: {
	app: "./index.ts"
  },

  experiments: {
    outputModule: true,
  },
  
  module: {
    rules: [
      {
        test: /\.ts?$/,
        use: 'ts-loader',
        exclude: /node_modules/,
      },
    ],
  },
  
  resolve: {
    extensions: ['.tsx', '.ts', '.js'],
  },

  output: {
	filename: 'index.js',
    path: `${__dirname}/dist`,
    library: {
      type: "module",
    },
  },
};
