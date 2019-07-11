type singleGif = {
  url: string,
  mp4: string,
  height: string,
  width: string,
};

type gifs = array(singleGif);

type gifsResponse = gifs;

let _decodeGif = gif =>
  Json.Decode.(
    gif
    |> at(["images", "fixed_height_small"], f =>
         {
           url: f |> field("url", string),
           mp4: f |> field("mp4", string),
           height: f |> field("height", string),
           width: f |> field("width", string),
         }
       )
  );

let decodeGifs = (json): gifsResponse => {
  let data = Json.Decode.(json |> field("data", data => data |> array(_decodeGif)));
  data;
};

let apiKey = "JL2ng3jv0WFkG1wVXDm71rtuzlx4sHi6";

let searchGifs = (text: string) =>
  Js.Promise.(
    Fetch.fetch(
      {j|https://api.giphy.com/v1/gifs/search?api_key=$apiKey&limit=25&offset=0&rating=G&lang=en&q=$text"|j},
    )
    |> then_(Fetch.Response.json)
    |> then_(json => json |> decodeGifs |> resolve)
  );
