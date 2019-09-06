type state = {
  isLoading: bool,
  response: option(GiphyApi.gifsResponse),
  error: option(Js.Promise.error),
};

let initialState = {isLoading: false, response: None, error: None};

type action =
  | FetchStarted
  | FetchSuccessful(GiphyApi.gifsResponse)
  | FetchFailed(Js.Promise.error);

let gifsListReducer = (state, action) => {
  switch (action) {
  | FetchStarted => {...state, isLoading: true, error: None}
  | FetchSuccessful(gifs) => {isLoading: false, error: None, response: Some(gifs)}
  | FetchFailed(err) => {isLoading: false, error: Some(err), response: None}
  };
};

[@react.component]
let make = (~searchTerm: string) => {
  React.null;
};
