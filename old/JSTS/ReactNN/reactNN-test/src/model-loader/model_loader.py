import tensorflow as tf
import os


def get_model_folders(directory):
    """
    Add each subdirectory in /models/ to a list and return that list.
    Assumption: only subfolders with valid neural network models are present under /models/.
    """
    model_folders = []
    items = os.listdir(directory)

    for item in items:
        item_path = os.path.join(directory, item)
        if os.path.isdir(item_path):
            model_folders.append(item)

    return model_folders


def load_models(model_folders, base_directory):
    loaded_models = {}
    for folder in model_folders:
        model_path = os.path.join(base_directory, folder)

        # disable eager execution (?)
        tf.compat.v1.disable_eager_execution()

        # loaded_model = tf.saved_model.load(model_path)
        loaded_model = tf.compat.v1.train.import_meta_graph(
            os.path.join(model_path, f'{folder}.meta'))

        loaded_models[folder] = loaded_model

    return loaded_models


if __name__ == '__main__':
    cwd = os.path.dirname(os.path.abspath(__file__))

    # All models should be stored in subfolders of /src/model-loader/models/
    directory = os.path.join(cwd, 'models')
    model_subfolders = get_model_folders(directory)

    found_models = load_models(model_subfolders, directory)
    print(f'Successfully loaded {len(found_models)} model(s)')

    # You can access the loaded models using their folder names as keys
    for folder, model in found_models.items():
        print(f"Loaded model from folder '{folder}'")
